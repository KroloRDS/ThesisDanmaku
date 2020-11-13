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
	cocos2d::DrawNode* drawNode = nullptr;

	const cocos2d::Vec2 ENEMY_HP_BAR_POS = cocos2d::Vec2(110, 878);
	const int ENEMY_HP_BAR_MAX_WIDTH = 660;
	const int ENEMY_HP_BAR_HEIGHT = 6;
};

