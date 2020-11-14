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
	if (iFrames > 0.0f)
	{
		iFrames -= delta;
	}
	else if (!defeated)
	{
		bulletPattern->update(delta);
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

void Enemy::defeat()
{
	defeated = true;
	hpBar->updateHpBar(0);

	auto emitter = cocos2d::ParticleExplosion::create();
	emitter->setPosition(Settings::getTranslatedCoords(absolutePos));
	emitter->setEndColor(cocos2d::Color4F::WHITE);
	emitter->setDuration(3.0f);
	addChild(emitter);

	sprite->runAction(cocos2d::FadeOut::create(1.0f));
}

void Enemy::nextPattern()
{
	int practicePattern = Settings::getPracticePattern();
	if (practicePattern != -1)
	{
		if (currentPattern > practicePattern)
		{
			currentPattern = -1;
		}
		else
		{
			currentPattern = practicePattern;
		}
	}

	createPattern(currentPattern);
}

void Enemy::createPattern(int pattern)
{
	iFrames = IFRAMES_AFTER_PATTERN_CHANGE;

	if (bulletPattern != nullptr)
	{
		bulletPattern->removeAllBullets();
		bulletPattern->removeFromParent();
	}

	switch (pattern)
	{
	case 0:
		bulletPattern = BulletPattern00::createBulletPattern(absolutePos);
		break;
	case 1:
		bulletPattern = BulletPattern01::createBulletPattern(absolutePos, player);
		break;
	case 2:
		bulletPattern = BulletPattern02::createBulletPattern(absolutePos, player);
		break;
	default:
		defeat();
		return;
	}

	addChild(bulletPattern);
	
	hp = bulletPattern->getHp();
	hpBar->setMaxHp(bulletPattern->getHp());
	hpBar->updateHpBar(hp);
	currentPattern++;
}
