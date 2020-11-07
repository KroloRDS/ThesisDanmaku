#include "Enemy.h"

Enemy* Enemy::createEnemy(std::string str, cocos2d::Vec2 pos)
{
	Enemy* ret = Enemy::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj(str, pos);

	ret->hpBar = EnemyHpBar::createEnemyHpBar();
	ret->addChild(ret->hpBar);
	ret->nextPattern();

	return ret;
}

void Enemy::update(float delta)
{
	if (iFrames <= 0.0f)
	{
		bulletPattern->update(delta);
	}
	else
	{
		iFrames -= delta;
	}
}

bool Enemy::isDefeated()
{
	return defeated;
}

BulletPattern* Enemy::getBulletPattern()
{
	return bulletPattern;
}

void Enemy::damage(int damage)
{
	if (iFrames > 0.0f)
	{
		return;
	}

	hp -= damage;

	if (hp <= 0)
	{
		currentPattern++;
		nextPattern();
	}

	hpBar->updateHpBar(hp);
}

void Enemy::nextPattern()
{
	iFrames = IFRAMES_AFTER_PATTERN_CHANGE;

	if (bulletPattern != nullptr)
	{
		bulletPattern->removeAllBullets();
		bulletPattern->removeFromParent();
	}

	switch (currentPattern)
	{
	case 0:
		bulletPattern = BulletPattern00::createBulletPattern(absolutePos);
		break;
	case 1:
		bulletPattern = BulletPattern99::createBulletPattern(absolutePos);
		break;
	default:
		defeated = true;
		return;
		break;
	}

	addChild(bulletPattern);
	hp = bulletPattern->getHp();
	
	hpBar->setMaxHp(bulletPattern->getHp());
	hpBar->updateHpBar(hp);
}
