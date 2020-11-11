#include <math.h>
#include "Bullet.h"

Bullet* Bullet::createBullet(cocos2d::Vec2 pos, int type, int subtype)
{
	Bullet* ret = Bullet::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj(ret->getSpriteName(type), pos);
	ret->createHitbox(type);
	ret->type = type;
	ret->subtype = subtype;
	ret->spawnAnimation();

	return ret;
}

void Bullet::spawnAnimation()
{
	if (type == LASER_SEGMENT)
	{
		return;
	}

	auto gameObj = GameObject::createGameObject("spawn.png", absolutePos);
	auto spawnSprite = gameObj->getSprite();
	spawnSprite->setOpacity(150);
	addChild(gameObj);
	
	switch (type)
	{
	case TEST:
		spawnSprite->setColor(cocos2d::Color3B(51, 153, 255));
		spawnSprite->setScale(Settings::getScale());
		break;
	case NORMAL:
		spawnSprite->setColor(cocos2d::Color3B(219, 0, 255));
		spawnSprite->setScale(Settings::getScale());
		break;
	case ARROWHEAD:
		spawnSprite->setColor(cocos2d::Color3B(0, 102, 255));
		spawnSprite->setScale(Settings::getScale());
		break;
	case BUTTERFLY:
		spawnSprite->setColor(cocos2d::Color3B(219, 0, 255));
		spawnSprite->setScale(Settings::getScale() * 1.5f);
		break;
	case MENTOS:
		spawnSprite->setColor(cocos2d::Color3B(255, 255, 255));
		spawnSprite->setScale(Settings::getScale() * 1.5f);
		break;
	case BUBBLE:
		spawnSprite->setColor(cocos2d::Color3B(255, 0, 0));
		spawnSprite->setScale(Settings::getScale() * 2.0f);
		break;
	default:
		break;
	}
	
	auto scaleTo = cocos2d::ScaleTo::create(0.5f, 0.0f);
	auto fadeTo = cocos2d::FadeTo::create(0.5f, 100);
	spawnSprite->runAction(cocos2d::Spawn::createWithTwoActions(scaleTo, fadeTo));
}

std::string Bullet::getSpriteName(int type)
{
	switch (type)
	{
	case TEST:
		return "test_bullet.png";
		break;
	case NORMAL:
		return "normal_bullet.png";
		break;
	case ARROWHEAD:
		return "arrowhead.png";
		break;
	case BUTTERFLY:
		return "butterfly.png";
		break;
	case MENTOS:
		return "mentos.png";
		break;
	case BUBBLE:
		return "bubble.png";
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
	case TEST:
		body = createTestHitbox();
		break;
	case NORMAL:
		body = createNormalBulletHitbox();
		break;
	case ARROWHEAD:
		body = createArrowheadHitbox();
		break;
	case BUTTERFLY:
		body = createCircularHitbox(7.0f);
		break;
	case MENTOS:
		body = createCircularHitbox(15.0f);
		break;
	case BUBBLE:
		body = createCircularHitbox(30.0f);
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

cocos2d::PhysicsBody* Bullet::createTestHitbox()
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

cocos2d::PhysicsBody* Bullet::createArrowheadHitbox()
{
	cocos2d::Vec2 polygon[4] = {
		cocos2d::Vec2(0, -14),
		cocos2d::Vec2(-4, -6),
		cocos2d::Vec2(4, -6),
		cocos2d::Vec2(0, 1)
	};

	auto body = cocos2d::PhysicsBody::create();
	body->addShape(cocos2d::PhysicsShapePolygon::create(polygon, 4));
	return body;
}

cocos2d::PhysicsBody* Bullet::createNormalBulletHitbox()
{
	cocos2d::Vec2 polygon[4] = {
		cocos2d::Vec2(0, -11),
		cocos2d::Vec2(-4, -2),
		cocos2d::Vec2(4, -2),
		cocos2d::Vec2(0, 10)
	};

	auto body = cocos2d::PhysicsBody::create();
	body->addShape(cocos2d::PhysicsShapePolygon::create(polygon, 4));
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
	age += delta;

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

int Bullet::getType()
{
	return type;
}

int Bullet::getSubtype()
{
	return subtype;
}

void Bullet::setSubtype(int newSubtype)
{
	subtype = newSubtype;
}

float Bullet::getAge()
{
	return age;
}

void Bullet::aimAt(cocos2d::Vec2 target, float angle)
{
	auto atan = atan2(target.x - absolutePos.x, target.y - absolutePos.y);
	setRot(atan * (float)(180.0f / M_PI) + angle);
}
