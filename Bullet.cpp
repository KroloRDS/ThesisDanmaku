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
	double ddelta = delta;
	auto newPosition = absolutePos;
	newPosition.x += ddelta * speed * sin(rotation / 180.0 * M_PI);
	newPosition.y += ddelta * speed * cos(rotation / 180.0 * M_PI);
	setPos(newPosition);
}

double Bullet::getSpeed()
{
	return speed;
}

void Bullet::setSpeed(double newSpeed)
{
	speed = newSpeed;
}

double Bullet::getRot()
{
	return rotation;
}

void Bullet::setRot(double newRotation)
{
	rotation = newRotation;
	sprite->setRotation(newRotation);
}
