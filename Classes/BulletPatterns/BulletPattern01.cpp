#include "BulletPattern01.h"
#include "Scenes/GameScene.h"

BulletPattern01* BulletPattern01::createBulletPattern(cocos2d::Vec2 origin, Player* player)
{
	BulletPattern01* ret = BulletPattern01::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initPattern(origin, "Playing Tag with a Tengu", ret->PATTERN_HP);
	ret->nextWave = ret->TIME_BETWEEN_WAVES;
	ret->player = player;

	ret->calcBulletMinMaxValues();

	return ret;
}

void BulletPattern01::calcBulletMinMaxValues()
{
	bulletMaxX = (int)GameScene::GAME_INNER_BOUNDS[2].x - 20;
	bulletMinX = (int)GameScene::GAME_INNER_BOUNDS[0].x + 20;
	bulletMaxY = (int)GameScene::GAME_INNER_BOUNDS[2].y - 20;
	bulletMinY = bulletMaxY - 350;

	randomBulletSpeedVariation = RANDOM_BULLET_MAX_SPEED - RANDOM_BULLET_MIN_SPEED;
}

void BulletPattern01::update(float delta)
{
	updateBullets(delta);

	if (nextRandomBulletSpawn > 0.0f)
	{
		nextRandomBulletSpawn -= delta;
	}
	else
	{
		float speed = (float)std::rand() / (float)RAND_MAX;
		bullets.push_back(Bullet::createBullet(origin, Bullet::BUTTERFLY));
		bullets.back()->setRot((float)std::rand() / (float)RAND_MAX * 360.0f);
		bullets.back()->setSpeed(speed * randomBulletSpeedVariation + RANDOM_BULLET_MIN_SPEED);
		addChild(bullets.back());

		nextRandomBulletSpawn += RANDOM_BULLET_SPAWN_INTERVAL;
	}

	if (nextWave > 0.0f)
	{
		nextWave -= delta;
		aim = player->getPos();
	}
	else
	{
		spawnBullets(delta);
	}
	
}

void BulletPattern01::spawnBullets(float delta)
{
	if (bulletsSpawned >= BULLETS_IN_WAVE)
	{
		nextWave = TIME_BETWEEN_WAVES;
		nextBulletSpawn = 0.0f;
		bulletsSpawned = 0;

		for (Bullet* bullet : bullets)
		{
			bullet->setSpeed(BULLET_SPEED);
		}

		return;
	}

	if (nextBulletSpawn > 0.0f)
	{
		nextBulletSpawn -= delta;
	}
	else
	{
		for (int i = 0; i < BULLETS_IN_BATCH; i++)
		{
			spawnBullet();
		}
	}
}

void BulletPattern01::spawnBullet()
{
	float x = (float)std::rand() / (float)RAND_MAX * (bulletMaxX - bulletMinX) + bulletMinX;
	float y = (float)std::rand() / (float)RAND_MAX * (bulletMaxY - bulletMinY) + bulletMinY;

	bullets.push_back(Bullet::createBullet(cocos2d::Vec2(x, y), Bullet::ARROWHEAD));
	bullets.back()->aimAt(cocos2d::Vec2(aim.x - origin.x + x, aim.y - origin.y + y));
	addChild(bullets.back());

	nextBulletSpawn = BULLET_SPAWN_INTERVAL;
	bulletsSpawned++;
}
