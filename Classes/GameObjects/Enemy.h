#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "Player.h"
#include "EnemyHpBar.h"
#include "BulletPatterns/BulletPattern00.h"
#include "BulletPatterns/BulletPattern01.h"
#include "BulletPatterns/BulletPattern02.h"
#include "BulletPatterns/BulletPattern99.h"

class Enemy : public GameObject
{
public:
	static Enemy* createEnemy(Player*);
	CREATE_FUNC(Enemy);
	void addChildren();
	void update(float);
	
	BulletPattern* getBulletPattern();
	float getIFrames();
	bool isDefeated();

	void nextPattern();
	void createPattern(int);
	int damage();
	void defeat();

private:
	BulletPattern* bulletPattern = nullptr;
	GameObject* positionIndicator = nullptr;
	EnemyHpBar* hpBar = nullptr;
	Player* player = nullptr;

	int currentPattern = 0;
	float iFrames = 0.0f;
	bool defeated = false;

	void updateIndicator();

	const cocos2d::Vec2 INIT_POS = cocos2d::Vec2(440, 600);
	const float IFRAMES_AFTER_PATTERN_CHANGE = 4.0f;
	const float INDICATOR_MAX_DISTANCE = 400.0f;
	const float INDICATOR_MIN_DISTANCE = 40.0f;
	const float POSITION_INDICATOR_Y = 30.0f;
};
