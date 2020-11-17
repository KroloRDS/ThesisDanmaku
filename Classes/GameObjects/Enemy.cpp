#include "Enemy.h"

Enemy* Enemy::createEnemy(Player* player)
{
	Enemy* ret = Enemy::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj("yukari", ret->INIT_POS);

	ret->hpBar = EnemyHpBar::createEnemyHpBar();
	ret->addChild(ret->hpBar);

	auto indicatorPos = cocos2d::Vec2(ret->INIT_POS.x, ret->POSITION_INDICATOR_Y);
	ret->positionIndicator = GameObject::createGameObject("enemy_indicator", indicatorPos);
	ret->addChild(ret->positionIndicator);
	
	ret->player = player;
	ret->nextPattern();

	return ret;
}

void Enemy::update(float delta)
{
	updateIndicator();

	if (iFrames > 0.0f)
	{
		iFrames -= delta;
	}
	else if (!defeated)
	{
		bulletPattern->update(delta);
		bulletPattern->getName()->update(delta);
	}
}

void Enemy::updateIndicator()
{
	float distance = player->getPos().x - positionIndicator->getPos().x;
	if (distance < 0.0f)
	{
		distance *= -1;
	}

	if (distance > INDICATOR_MAX_DISTANCE)
	{
		distance = INDICATOR_MAX_DISTANCE;
	}
	else if (distance < INDICATOR_MIN_DISTANCE)
	{
		distance = INDICATOR_MIN_DISTANCE;
	}

	positionIndicator->getSprite()->setOpacity(uint8_t(distance / INDICATOR_MAX_DISTANCE * 255.0f));
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
	int hp = bulletPattern->damage();
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
	
	hpBar->setMaxHp(bulletPattern->getMaxHp());
	currentPattern++;
}
