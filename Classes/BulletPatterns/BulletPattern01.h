#pragma once

#include "cocos2d.h"
#include "BulletPattern.h"

class BulletPattern01 : public BulletPattern
{
public:
	static BulletPattern01* createBulletPattern(cocos2d::Vec2, Player*);
	CREATE_FUNC(BulletPattern01);
	void update(float);
private:
	cocos2d::Vec2 origin = cocos2d::Vec2(0, 0);
	
	float nextBubbleInterval = 0.0f;

	float mentosRotation = 0.0f;
	float mentosRotationSpeed = 10.0f;
	float nextMentosInterval = 0.0f;

	float bounceMentosRotation = 0.0f;
	float bounceMentosRotationSpeed = 150.0f;
	float nextBounceMentosInterval = 0.0f;

	int randomMentosMaxX;
	int randomMentosMinX;
	int randomMentosMaxY;
	int randomMentosMinY;
	float nextRandomMentosInterval = 0.0f;

	float laserRotation = 0.0f;
	float laserRotationSpeed = 3.0f;

	float arrowheadRotation = 0.0f;
	float arrowheadRotationSpeed = 5.0f;
	float nextArrowheadInterval = 0.0f;

	void createLasers();
	void calcRandomMentosMinMaxValues();

	void spawnBubbles(float);
	void spawnMentos(float);
	void spawnBounceMentos(float);
	void spawnRandomMentos(float);
	void spawnArrowheads(float);

	const float BUBBLE_SPEED = 400.0f;
	const float BUBBLE_ANGLE_DIFF = 50.0f;
	const float BUBBLE_SPAWN_INTERVAL = 0.8f;

	const float MENTOS_SPEED = 300.0f;
	const float MENTOS_ANGLE_MIN = 90.0f;
	const float MENTOS_ANGLE_MAX = 270.0f;
	const float MENTOS_SPAWN_INTERVAL = 0.03f;

	const float BOUNCE_MENTOS_SPEED = 400.0f;
	const float BOUNCE_MENTOS_ANGLE_MIN = -90.0f;
	const float BOUNCE_MENTOS_ANGLE_MAX = 90.0f;
	const float BOUNCE_MENTOS_SPAWN_INTERVAL = 0.2f;

	const int RANDOM_MENTOS_IN_BATCH = 2;
	const float RANDOM_MENTOS_BASE_ANGLE = 170.0f;
	const float RANDOM_MENTOS_ANGLE_VARIATION = 20.0f;
	const float RANDOM_MENTOS_SPAWN_INTERVAL = 0.6f;

	const float LASER_ANGLE_MIN = 177.0f;
	const float LASER_ANGLE_MAX = 185.0f;

	const float ARROWHEAD_SPEED = 1000.0f;
	const float ARROWHEAD_ANGLE_MIN = 177.0f;
	const float ARROWHEAD_ANGLE_MAX = 195.0f;
	const float ARROWHEAD_SPAWN_INTERVAL = 0.05f;
	const float ARROWHEAD_ANGLE_BETWEEN_ARMS = 40.00f;
	const cocos2d::Vec2 ARROWHEAD_SPAWN_POINTS[4] = {
		cocos2d::Vec2(340, 800),
		cocos2d::Vec2(540, 800),
		cocos2d::Vec2(640, 660),
		cocos2d::Vec2(240, 660)
	};

	const int PATTERN_HP = 1000;
};

