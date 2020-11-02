#include <math.h>
#include "Bullet.h"

Bullet* Bullet::createBullet(int type, cocos2d::Vec2 pos)
{
	Bullet* ret = Bullet::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj(ret->getSpriteName(type), pos);
	ret->createHitbox(type);

	return ret;
}

std::string Bullet::getSpriteName(int type)
{
	switch (type)
	{
	case ARROWHEAD:
		return "bullet.png";
		break;
	case LASER_SEGMENT:
		return "laser.png";
		break;
	default:
		return "";
		break;
	}
}

void Bullet::createHitbox(int type)
{
	cocos2d::PhysicsBody* body = nullptr;

	switch (type)
	{
	case ARROWHEAD:
		body = createArrowheadHitbox();
		break;
	case LASER_SEGMENT:
		body = createRectangularHitbox(-8, -8, 16, 16);
		break;
	default:
		body = cocos2d::PhysicsBody::create();
		break;
	}

	body->setDynamic(false);
	body->setCategoryBitmask(0x2);
	body->setContactTestBitmask(0x5);
	sprite->setPhysicsBody(body);
}

cocos2d::PhysicsBody* Bullet::createArrowheadHitbox()
{
	cocos2d::Vec2 triangleLeft[3] = {
		cocos2d::Vec2(0, 8),
		cocos2d::Vec2(-1, -8),
		cocos2d::Vec2(-6, -11)
	};

	cocos2d::Vec2 triangleRight[3] = {
		cocos2d::Vec2(-1, 8),
		cocos2d::Vec2(-1, -8),
		cocos2d::Vec2(6, -11)
	};

	auto body = cocos2d::PhysicsBody::create();
	body->addShape(cocos2d::PhysicsShapePolygon::create(triangleLeft, 3));
	body->addShape(cocos2d::PhysicsShapePolygon::create(triangleRight, 3));
	return body;
}

cocos2d::PhysicsBody* Bullet::createRectangularHitbox(float x, float y, float width, float height)
{
	cocos2d::Vec2 rectange[4] = {
		cocos2d::Vec2(x, y),
		cocos2d::Vec2(x + width, y),
		cocos2d::Vec2(x + width, y + height),
		cocos2d::Vec2(x, y + height)
	};

	auto body = cocos2d::PhysicsBody::create();
	body->addShape(cocos2d::PhysicsShapePolygon::create(rectange, 4));
	return body;
}

cocos2d::PhysicsBody* Bullet::createCircularHitbox(float r)
{
	return cocos2d::PhysicsBody::createCircle(r * Settings::getScale());
}

void Bullet::update(float delta)
{
	auto newPosition = absolutePos;
	newPosition.x += delta * speed * xRotationCoeff;
	newPosition.y += delta * speed * yRotationCoeff;
	setPos(newPosition);
}

float Bullet::getSpeed()
{
	return speed;
}

void Bullet::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

float Bullet::getRot()
{
	return rotation;
}

void Bullet::setRot(float newRotation)
{
	rotation = newRotation;
	sprite->setRotation(rotation);
	xRotationCoeff = (float)sin(rotation / 180.0f * M_PI);
	yRotationCoeff = (float)cos(rotation / 180.0f * M_PI);
}
