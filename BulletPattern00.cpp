#include "BulletPattern00.h"

const float BulletPattern00::BULLET_INTERVAL = 0.06;
const float BulletPattern00::BULLET_SPEED = 500.0;
const float BulletPattern00::MAX_ROTATION_SPEED = 5.0;

BulletPattern00* BulletPattern00::createBulletPattern00()
{
	BulletPattern00* ret = BulletPattern00::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}
	return ret;
}

void BulletPattern00::update(float delta)
{
	spawnNewBullets(delta);
	updateBullets(delta);

	rotationSpeed += acceleration;
	rotation += rotationSpeed;
	rotation = fmod(rotation, 360.0);

	if (abs(rotationSpeed) > MAX_ROTATION_SPEED)
	{
		acceleration *= -1;
	}
}

void BulletPattern00::spawnNewBullets(float delta)
{
	if (nextBulletInterval > 0.0)
	{
		nextBulletInterval -= delta;
	}
	else
	{
		for (int i = 0; i < ARMS_COUNT; i++)
		{
			bullets.pushBack(Bullet::createBullet("bullet.png", cocos2d::Vec2(440, 600)));
			bullets.back()->setSpeed(BULLET_SPEED);
			bullets.back()->setRot(rotation + i * 360.0 / ARMS_COUNT);
			addChild(bullets.back());
		}
		nextBulletInterval += BULLET_INTERVAL;
	}
}
