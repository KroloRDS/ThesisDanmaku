#include "Enemy.h"

const cocos2d::Vec2 Enemy::INIT_POS = cocos2d::Vec2(440, 600);

Enemy* Enemy::createEnemy(Player* player)
{
	Enemy* ret = Enemy::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj("yukari.png", INIT_POS);

	ret->hpBar = EnemyHpBar::createEnemyHpBar();
	ret->addChild(ret->hpBar);
	ret->player = player;
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

float Enemy::getIFrames()
{
	return iFrames;
}

int Enemy::damage()
{
	hp--;
	hpBar->updateHpBar(hp);
	return hp;
}

void Enemy::nextPattern()
{
	//iFrames = IFRAMES_AFTER_PATTERN_CHANGE;

	int practicePattern = Settings::getPracticePattern();
	if (practicePattern != 0)
	{
		currentPattern = practicePattern;
		defeated = true;
	}
	else
	{
		currentPattern++;
	}

	if (bulletPattern != nullptr)
	{
		bulletPattern->removeAllBullets();
		bulletPattern->removeFromParent();
	}

	switch (currentPattern)
	{
	case 1:
		bulletPattern = BulletPattern00::createBulletPattern(absolutePos);
		break;
	case 2:
		bulletPattern = BulletPattern01::createBulletPattern(absolutePos, player);
		break;
	case 3:
		bulletPattern = BulletPattern02::createBulletPattern(absolutePos, player);
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
