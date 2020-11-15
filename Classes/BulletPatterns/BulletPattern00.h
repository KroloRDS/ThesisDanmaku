#pragma once

#include "cocos2d.h"
#include "BulletPattern.h"

class BulletPattern00 : public BulletPattern
{
public:
	static BulletPattern00* createBulletPattern(cocos2d::Vec2);
	CREATE_FUNC(BulletPattern00);
	void update(float);
private:
	float nextBulletInterval = 0.0f;
	float rotation = 0.0f;
	float rotationSpeed = 0.0f;
	float acceleration = 0.02f;

	void spawnNewBullets(float);

	const int ARMS_COUNT = 8;
	const float BULLET_INTERVAL = 0.03f;
	const float BULLET_SPEED = 500.0f;
	const float MAX_ROTATION_SPEED = 5.0f;

	const int PATTERN_HP = 1000;
};
