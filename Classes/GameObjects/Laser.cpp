#include "Laser.h"

Laser* Laser::createLaser(cocos2d::Vec2 origin, float rotation)
{
	Laser* ret = Laser::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->origin = origin;
	ret->setRotation(rotation);
	return ret;
}

void Laser::update(float delta)
{
	nextSpawn -= delta;

	if (nextSpawn <= 0.0f)
	{
		segments.push_back(Bullet::createBullet(origin, Bullet::LASER_SEGMENT));
		segments.back()->setRot(rotation);
		segments.back()->setSpeed(500.0f);
		addChild(segments.back());

		nextSpawn += SEGMENT_SPAWN_RATE;
	}

	for (Bullet* segment : segments)
	{
		segment->update(delta);
	}
}

void Laser::move(float x, float y)
{
	origin.x += x;
	origin.y += y;

	for (Bullet* segment : segments)
	{
		segment->setPos(cocos2d::Vec2(segment->getPos().x + x, segment->getPos().y + y));
	}
}

cocos2d::Vec2 Laser::getOrigin()
{
	return origin;
}

void Laser::setRotation(float newRotation)
{
	float oldXCoeff = (float)sin(rotation / 180.0f * M_PI);
	float oldYCoeff = (float)cos(rotation / 180.0f * M_PI);
	float newXCoeff = (float)sin(newRotation / 180.0f * M_PI);
	float newYCoeff = (float)cos(newRotation / 180.0f * M_PI);

	for (Bullet* segment : segments)
	{
		auto oldPos = segment->getPos();
		float diffX = origin.x - oldPos.x;
		float diffY = origin.y - oldPos.y;
		float radius = sqrt(diffX * diffX + diffY * diffY);

		segment->setRot(newRotation);
		segment->setPos(cocos2d::Vec2(origin.x + (radius * newXCoeff), origin.y + (radius * newYCoeff)));
	}

	rotation = newRotation;
}

float Laser::getRotation()
{
	return rotation;
}

std::vector<Bullet*>& Laser::getSegments()
{
	return segments;
}
