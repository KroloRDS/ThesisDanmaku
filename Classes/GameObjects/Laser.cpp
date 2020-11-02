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
		segments.push_back(Bullet::createBullet(Bullet::LASER_SEGMENT, origin));
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

/*
void Laser::updateSegments()
{
	int segmentCount = 0;
	auto segmentPosition = origin;
	float xRotationCoeff = (float)sin(rotation / 180.0f * M_PI);
	float yRotationCoeff = (float)cos(rotation / 180.0f * M_PI);

	auto it = segments.rbegin();
	while (it.base() != segments.begin())
	{
		segmentPosition.x = origin.x + segmentCount * SEGMENT_OFFSET * xRotationCoeff;
		segmentPosition.y = origin.y + segmentCount * SEGMENT_OFFSET * yRotationCoeff;

		(*it)->setPos(segmentPosition);
		(*it)->setRot(rotation);

		segmentCount++;
		it++;
	}
}
*/

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
		int diffX = origin.x - oldPos.x;
		int diffY = origin.y - oldPos.y;
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
