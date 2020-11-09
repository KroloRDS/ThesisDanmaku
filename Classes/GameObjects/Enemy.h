#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "Player.h"
#include "EnemyHpBar.h"
#include "BulletPatterns/BulletPattern00.h"
#include "BulletPatterns/BulletPattern01.h"
#include "BulletPatterns/BulletPattern99.h"

class Enemy : public GameObject
{
public:
	static Enemy* createEnemy(std::string, Player*);
	CREATE_FUNC(Enemy);
	void update(float);
	
	BulletPattern* getBulletPattern();
	float getIFrames();
	bool isDefeated();

	void nextPattern();
	int damage();

private:
	BulletPattern* bulletPattern = nullptr;
	EnemyHpBar* hpBar = nullptr;
	Player* player = nullptr;
	int hp = 0;
	int currentPattern = 0;
	float iFrames = 0.0f;
	bool defeated = false;

	const float IFRAMES_AFTER_PATTERN_CHANGE = 3.0f;
	static const cocos2d::Vec2 INIT_POS;
};
