#include "EnemyHpBar.h"

EnemyHpBar* EnemyHpBar::createEnemyHpBar()
{
	EnemyHpBar* ret = EnemyHpBar::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->bar = cocos2d::DrawNode::create();
	ret->outline = cocos2d::DrawNode::create();
	ret->addChild(ret->outline);
	ret->addChild(ret->bar);
	ret->setLocalZOrder(2);
	return ret;
}

void EnemyHpBar::updateHpBar(int hp)
{
	auto dest = ENEMY_HP_BAR_POS;
	dest.y += (float)ENEMY_HP_BAR_HEIGHT;
	dest.x += (float)ENEMY_HP_BAR_MAX_WIDTH * (float)hp / (float)maxHp;

	auto outlineDest = cocos2d::Vec2(dest.x + OUTLINE_THICKNESS, dest.y + OUTLINE_THICKNESS);
	
	auto origin = Settings::getTranslatedCoords(ENEMY_HP_BAR_POS);
	dest = Settings::getTranslatedCoords(dest);

	auto outlineOrigin = Settings::getTranslatedCoords(ENEMY_HP_BAR_OUTLINE_POS);
	outlineDest = Settings::getTranslatedCoords(outlineDest);
	
	bar->clear();
	outline->clear();
	bar->drawSolidRect(origin, dest, cocos2d::Color4F::WHITE);
	outline->drawSolidRect(outlineOrigin, outlineDest, cocos2d::Color4F::BLACK);
}

void EnemyHpBar::setMaxHp(int newMax)
{
	maxHp = newMax;
	updateHpBar(maxHp);
}
