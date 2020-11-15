#include "EnemyHpBar.h"

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
	auto dest = ENEMY_HP_BAR_POS;
	dest.y += (float)ENEMY_HP_BAR_HEIGHT;
	dest.x += (float)ENEMY_HP_BAR_MAX_WIDTH * (float)hp / (float)maxHp;
	
	auto origin = Settings::getTranslatedCoords(ENEMY_HP_BAR_POS);
	dest = Settings::getTranslatedCoords(dest);
	
	drawNode->clear();
	drawNode->drawSolidRect(origin, dest, cocos2d::Color4F::WHITE);
}

void EnemyHpBar::setMaxHp(int newMax)
{
	maxHp = newMax;
	updateHpBar(maxHp);
}
