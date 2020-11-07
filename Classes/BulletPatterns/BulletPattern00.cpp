#include "BulletPattern00.h"

BulletPattern00* BulletPattern00::createBulletPattern(cocos2d::Vec2 origin)
{
	BulletPattern00* ret = BulletPattern00::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}
	ret->origin = origin;
	ret->hp = ret->PATTERN_HP;
	ret->rotation = (float)std::rand() / (float)RAND_MAX * (360.0f / (float)ret->ARMS_COUNT);
	return ret;
}

void BulletPattern00::update(float delta)
{
	spawnNewBullets(delta);
	updateBullets(delta);

	rotationSpeed += acceleration * delta * 60.0f;
	rotation += rotationSpeed;
	rotation = fmod(rotation, 360.0f);

	acceleration *= abs(rotationSpeed) > MAX_ROTATION_SPEED ? -1.0f : 1.0f;
}

void BulletPattern00::spawnNewBullets(float delta)
{
	if (nextBulletInterval > 0.0f)
	{
		nextBulletInterval -= delta;
		return;
	}
	
	for (int i = 0; i < ARMS_COUNT; i++)
	{
		bullets.push_back(Bullet::createBullet(origin, Bullet::TEST_BULLET));
		bullets.back()->setSpeed(BULLET_SPEED);
		bullets.back()->setRot(rotation + i * 360.0f / ARMS_COUNT);
		addChild(bullets.back());
	}
	nextBulletInterval += BULLET_INTERVAL;
}
