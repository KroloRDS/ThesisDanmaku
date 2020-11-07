#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "EnemyHpBar.h"
#include "BulletPatterns/BulletPattern00.h"
#include "BulletPatterns/BulletPattern99.h"

class Enemy : public GameObject
{
public:
	static Enemy* createEnemy(std::string, cocos2d::Vec2);
	CREATE_FUNC(Enemy);
	void update(float);
	
	BulletPattern* getBulletPattern();

	void damage(int damage = 1);
	bool isDefeated();

private:
	BulletPattern* bulletPattern = nullptr;
	EnemyHpBar* hpBar = nullptr;
	int hp = 0;
	int currentPattern = 0;
	float iFrames = 0.0f;
	bool defeated = false;

	void nextPattern();

	const float IFRAMES_AFTER_PATTERN_CHANGE = 3.0f;
};
