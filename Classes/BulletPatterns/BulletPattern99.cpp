#include "BulletPattern99.h"

BulletPattern99* BulletPattern99::createBulletPattern(cocos2d::Vec2 origin)
{
	BulletPattern99* ret = BulletPattern99::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}
	ret->origin = origin;
	ret->createLasers();
	ret->hp = 1000;
	return ret;
}

void BulletPattern99::createLasers()
{
	for (int i = 0; i < ARMS_COUNT; i++)
	{
		lasers.push_back(Laser::createLaser(origin, rotation + i * (360.0f / ARMS_COUNT)));
		addChild(lasers.back());
	}
}

void BulletPattern99::update(float delta)
{
	updateBullets(delta);
	
	rotation = fmod(rotation, 360.0f);
	rotation += 1.0f;

	int count = 0;
	auto it = lasers.begin();
	while (it != lasers.end())
	{
		(*it)->move(0.5f, 0.0f);
		(*it)->setRotation(rotation + count * (360.0f / ARMS_COUNT));
		count++;
		it++;
	}
}