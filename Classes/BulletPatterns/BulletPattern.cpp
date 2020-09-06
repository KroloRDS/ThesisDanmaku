#include "BulletPattern.h"

cocos2d::Vector<Bullet*>& BulletPattern::getBullets()
{
	return bullets;
}

void BulletPattern::updateBullets(float delta)
{
	for (Bullet* bullet : bullets)
	{
		bullet->update(delta);
	}
}
