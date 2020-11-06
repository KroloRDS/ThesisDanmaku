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
	ret->drawNode->setScale(Settings::getScale());
	ret->addChild(ret->drawNode);
	return ret;
}

void EnemyHpBar::updateHpBar(int hp)
{
	drawNode->clear();
	int width = ENEMY_HP_BAR_MAX_WIDTH * hp / maxHp;
	cocos2d::Vec2 dest(ENEMY_HP_BAR_POS.x + width, ENEMY_HP_BAR_POS.y + ENEMY_HP_BAR_HEIGHT);
	drawNode->drawSolidRect(ENEMY_HP_BAR_POS, dest, COLOR_WHITE);
}

void EnemyHpBar::setMaxHp(int newMax)
{
	maxHp = newMax;
}
