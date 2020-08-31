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
	return ret;
}

void Bullet::update(float delta)
{
	auto newPosition = absolutePos;
	newPosition.x += delta * speed * (float)sin(rotation / 180.0f * M_PI);
	newPosition.y += delta * speed * (float)cos(rotation / 180.0f * M_PI);
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
	sprite->setRotation(newRotation);
}
