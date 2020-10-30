#pragma once

#include "cocos2d.h"
#include "HelperClasses/Settings.h"

class EnemyHpBar : public cocos2d::Node
{
public:
	static EnemyHpBar* createEnemyHpBar(int);
	CREATE_FUNC(EnemyHpBar);
	void updateHpBar(int);

private:
	int maxHp = 0;
	cocos2d::DrawNode* drawNode = nullptr;

	static const cocos2d::Color4F COLOR_WHITE;
	static const cocos2d::Vec2 ENEMY_HP_BAR_POS;
	static const int ENEMY_HP_BAR_MAX_WIDTH = 660;
	static const int ENEMY_HP_BAR_HEIGHT = 6;
};

