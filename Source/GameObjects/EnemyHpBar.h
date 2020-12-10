#pragma once

#include "cocos2d.h"
#include "HelperClasses/Settings.h"

class EnemyHpBar : public cocos2d::Node
{
public:
	static EnemyHpBar* createEnemyHpBar();
	CREATE_FUNC(EnemyHpBar);
	void updateHpBar(int);
	void setMaxHp(int);

private:
	int maxHp = 0;
	cocos2d::DrawNode* bar = nullptr;
	cocos2d::DrawNode* outline = nullptr;

	const int ENEMY_HP_BAR_MAX_WIDTH = 660;
	const int ENEMY_HP_BAR_HEIGHT = 6;
	
	const float OUTLINE_THICKNESS = 2.0f;
	const float ENEMY_HP_BAR_POS_X = 110.0f;
	const float ENEMY_HP_BAR_POS_Y = 878.0f;

	const cocos2d::Vec2 ENEMY_HP_BAR_POS = cocos2d::Vec2(
		ENEMY_HP_BAR_POS_X,
		ENEMY_HP_BAR_POS_Y
	);
	const cocos2d::Vec2 ENEMY_HP_BAR_OUTLINE_POS = cocos2d::Vec2(
		ENEMY_HP_BAR_POS_X - OUTLINE_THICKNESS,
		ENEMY_HP_BAR_POS_Y - OUTLINE_THICKNESS
	);
};

