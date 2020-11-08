#include "Enemy.h"

Enemy* Enemy::createEnemy(std::string str, cocos2d::Vec2 pos, Player* player)
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
	ret->player = player;
	ret->nextPattern();

	return ret;
}

void Enemy::update(float delta)
{
	collision(player->getBullets());
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

void Enemy::collision(std::vector<PlayerBullet*>& vec)
{
	auto it = vec.begin();
	while (it != vec.end())
	{
		if ((*it)->getSpriteBoundingBox().intersectsRect(getSpriteBoundingBox()))
		{
			damage();
			damageAnimation((*it)->getPos());

			(*it)->removeFromParent();
			it = vec.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Enemy::damage()
{
	if (iFrames > 0.0f)
	{
		return;
	}

	hp--;

	if (hp <= 0)
	{
		currentPattern++;
		nextPattern();
	}

	hpBar->updateHpBar(hp);
}

void Enemy::damageAnimation(cocos2d::Vec2 pos)
{
	auto dmgSprite = cocos2d::Sprite::create("damage.png");
	dmgSprite->setScale(Settings::getScale() * 1.5f);
	dmgSprite->setPosition(pos.x, pos.y + 50);
	dmgSprite->setOpacity(150);
	addChild(dmgSprite);

	dmgSprite->runAction(cocos2d::FadeTo::create(0.3f, 0));
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
		bulletPattern = BulletPattern01::createBulletPattern(absolutePos, player);
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
