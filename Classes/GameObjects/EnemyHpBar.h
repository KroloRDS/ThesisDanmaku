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
	const int OUTLINE_THICKNESS = 2;

	const cocos2d::Vec2 ENEMY_HP_BAR_POS = cocos2d::Vec2(110, 878);
	const cocos2d::Vec2 ENEMY_HP_BAR_OUTLINE_POS =
		cocos2d::Vec2(110 - OUTLINE_THICKNESS, 878 - OUTLINE_THICKNESS);
};

