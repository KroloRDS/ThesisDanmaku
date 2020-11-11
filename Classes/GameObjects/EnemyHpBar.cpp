#include "EnemyHpBar.h"

const cocos2d::Color4F EnemyHpBar::COLOR_WHITE = cocos2d::Color4F(1, 1, 1, 1);
const cocos2d::Vec2 EnemyHpBar::ENEMY_HP_BAR_POS = cocos2d::Vec2(110, 878);

EnemyHpBar* EnemyHpBar::createEnemyHpBar()
{
	EnemyHpBar* ret = EnemyHpBar::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->drawNode = cocos2d::DrawNode::create();
	ret->addChild(ret->drawNode);
	return ret;
}

void EnemyHpBar::updateHpBar(int hp)
{
	auto origin = ENEMY_HP_BAR_POS;
	float width = (float)ENEMY_HP_BAR_MAX_WIDTH * (float)hp / (float)maxHp;
	cocos2d::Vec2 dest(origin.x + width, origin.y + (float)ENEMY_HP_BAR_HEIGHT);

	origin *= Settings::getScale();
	origin.x += Settings::getHorizontalOffset();
	dest *= Settings::getScale();
	dest.x += Settings::getHorizontalOffset();
	
	drawNode->clear();
	drawNode->drawSolidRect(origin, dest, COLOR_WHITE);
}

void EnemyHpBar::setMaxHp(int newMax)
{
	maxHp = newMax;
}
