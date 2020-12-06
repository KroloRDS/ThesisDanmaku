#include "Enemy.h"

Enemy* Enemy::createEnemy(Player* player)
{
	Enemy* ret = Enemy::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj("enemy", ret->INIT_POS);
	ret->hpBar = EnemyHpBar::createEnemyHpBar();

	ret->positionIndicator = GameObject::createGameObject("enemy_indicator", cocos2d::Vec2(0, 0));
	ret->positionIndicator->setLocalZOrder(3);
	
	ret->player = player;
	ret->nextPattern();

	return ret;
}

void Enemy::addChildren()
{
	getParent()->addChild(bulletPattern->getName());
	getParent()->addChild(positionIndicator);
	getParent()->addChild(hpBar);
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
	positionIndicator->setPos(cocos2d::Vec2(getPos().x, POSITION_INDICATOR_Y));
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

	if (hp > bulletPattern->getMaxHp() / 4)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemy_hit.mp3");
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemy_hit_low_hp.mp3");
	}

	return hp;
}

void Enemy::defeat()
{
	defeated = true;
	hpBar->updateHpBar(0);

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemy_defeated.mp3");

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
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/spell_card.mp3");

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
