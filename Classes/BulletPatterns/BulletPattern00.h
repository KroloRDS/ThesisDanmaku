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
	cocos2d::Vec2 origin = cocos2d::Vec2(0, 0);

	void spawnNewBullets(float);

	static const int ARMS_COUNT = 8;
	static const float BULLET_INTERVAL;
	static const float BULLET_SPEED;
	static const float MAX_ROTATION_SPEED;
	static const int PATTERN_HP = 1000;

	float nextBulletInterval = 0.0f;
	float rotation = 0.0f;
	float rotationSpeed = 0.0f;
	float acceleration = 0.02f;
};
