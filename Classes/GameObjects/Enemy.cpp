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

	ret->bulletPattern = BulletPattern00::createBulletPattern00(pos);
	ret->addChild(ret->bulletPattern);
	ret->hp = ret->bulletPattern->getHp();

	ret->hpBar = EnemyHpBar::createEnemyHpBar(ret->hp);
	ret->hpBar->updateHpBar(ret->hp);
	ret->addChild(ret->hpBar);

	return ret;
}

void Enemy::update(float delta)
{
	bulletPattern->update(delta);
}

std::vector<Bullet*>& Enemy::getBullets()
{
	return bulletPattern->getBullets();
}

int Enemy::getHp()
{
	return hp;
}

int Enemy::getMaxHp()
{
	return bulletPattern->getHp();
}

void Enemy::damage(int damage)
{
	hp -= damage;
	hpBar->updateHpBar(hp);
}
