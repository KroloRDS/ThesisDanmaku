#include "BulletPattern.h"

void BulletPattern::updateBullets(float delta)
{
	cocos2d::Vector<Bullet*> bulletsToKeep = {};
	for (Bullet* bullet : bullets)
	{
		if (bullet->isOutOfBounds())
		{
			bullet->removeFromParent();
		}
		else
		{
			bulletsToKeep.pushBack(bullet);
			bullet->update(delta);
		}
	}
	bullets = bulletsToKeep;
}
