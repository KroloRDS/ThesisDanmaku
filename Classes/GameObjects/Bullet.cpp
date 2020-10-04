#include <math.h>
#include "Bullet.h"

Bullet* Bullet::createBullet(std::string str, cocos2d::Vec2 pos)
{
	Bullet* ret = Bullet::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj(str, pos);
	ret->sprite->setPhysicsBody(createBody());

	return ret;
}

cocos2d::PhysicsBody* Bullet::createBody()
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
	body->setDynamic(false);
	body->setCategoryBitmask(0x2);
	body->setContactTestBitmask(0x1);
	return body;
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
