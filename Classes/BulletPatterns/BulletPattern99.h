#pragma once

#include "cocos2d.h"
#include "BulletPattern.h"

class BulletPattern99 : public BulletPattern
{
public:
	static BulletPattern99* createBulletPattern(cocos2d::Vec2);
	CREATE_FUNC(BulletPattern99);
	void update(float);
private:
	cocos2d::Vec2 origin = cocos2d::Vec2(0, 0);
	float rotation = 0.0f;

	void createLasers();

	static const int ARMS_COUNT = 4;
};

