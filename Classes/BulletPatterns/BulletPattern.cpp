#include "BulletPattern.h"

std::vector<Bullet*>& BulletPattern::getBullets()
{
	return bullets;
}

int BulletPattern::getHp()
{
	return hp;
}

void BulletPattern::updateBullets(float delta)
{
	for (Bullet* bullet : bullets)
	{
		bullet->update(delta);
	}
}
