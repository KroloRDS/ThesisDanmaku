#include "BulletPattern00.h"

const float BulletPattern00::BULLET_INTERVAL = 0.06f;
const float BulletPattern00::BULLET_SPEED = 500.0f;
const float BulletPattern00::MAX_ROTATION_SPEED = 5.0f;

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

	rotationSpeed += acceleration * delta * 60.0f;
	rotation += rotationSpeed;
	rotation = fmod(rotation, 360.0f);

	if (abs(rotationSpeed) > MAX_ROTATION_SPEED)
	{
		acceleration *= -1.0f;
	}
}

void BulletPattern00::spawnNewBullets(float delta)
{
	if (nextBulletInterval > 0.0f)
	{
		nextBulletInterval -= delta;
	}
	else
	{
		for (int i = 0; i < ARMS_COUNT; i++)
		{
			bullets.pushBack(Bullet::createBullet("bullet.png", cocos2d::Vec2(440, 600)));
			bullets.back()->setSpeed(BULLET_SPEED);
			bullets.back()->setRot(rotation + i * 360.0f / ARMS_COUNT);
			addChild(bullets.back());
		}
		nextBulletInterval += BULLET_INTERVAL;
	}
}