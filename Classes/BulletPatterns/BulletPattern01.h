#pragma once
#include "BulletPattern.h"

class BulletPattern01 : public BulletPattern
{
public:
	static BulletPattern01* createBulletPattern(cocos2d::Vec2, Player*);
	CREATE_FUNC(BulletPattern01);
	void update(float);
private:
	cocos2d::Vec2 aim = cocos2d::Vec2(0, 0);

	int bulletsSpawned = 0;
	float nextWave = 0.0f;
	float nextBulletSpawn = 0.0f;
	float nextRandomBulletSpawn = 0.0f;

	int bulletMaxX = 0;
	int bulletMinX = 0;
	int bulletMaxY = 0;
	int bulletMinY = 0;
	float randomBulletSpeedVariation = 0.0f;

	void calcBulletMinMaxValues();
	void spawnBullets(float);
	void spawnBullet();

	const int BULLETS_IN_WAVE = 100;
	const int BULLETS_IN_BATCH = 3;
	const float TIME_BETWEEN_WAVES = 5.0f;
	const float BULLET_SPEED = 500.0f;
	const float BULLET_SPAWN_INTERVAL = 0.002f;
	
	const float RANDOM_BULLET_MIN_SPEED = 400.0f;
	const float RANDOM_BULLET_MAX_SPEED = 400.0f;
	const float RANDOM_BULLET_SPAWN_INTERVAL = 0.005f;

	const int PATTERN_HP = 1000;
};

