#include "BulletPattern.h"

void BulletPattern::initPattern(cocos2d::Vec2 origin, std::string name, int hp)
{
	this->name = PatternName::createPatternName(name);
	this->origin = origin;
	this->maxHp = hp;
	this->hp = hp;
}

std::vector<Bullet*>& BulletPattern::getBullets()
{
	return bullets;
}

std::vector<Laser*>& BulletPattern::getLasers()
{
	return lasers;
}

PatternName* BulletPattern::getName()
{
	return name;
}

int BulletPattern::getMaxHp()
{
	return maxHp;
}

int BulletPattern::getHp()
{
	return hp;
}

int BulletPattern::damage()
{
	hp--;
	return hp;
}

void BulletPattern::updateBullets(float delta)
{
	for (Laser* laser : lasers)
	{
		laser->update(delta);
		removeOutOfBoundsObjects(laser->getSegments());
	}

	for (Bullet* bullet : bullets)
	{
		bullet->update(delta);
	}

	removeOutOfBoundsObjects(bullets);
}

void BulletPattern::removeAllBullets()
{
	removeAllObjects(bullets);
	for (Laser* laser : lasers)
	{
		removeAllObjects(laser->getSegments());
	}
}

void BulletPattern::removeAllObjects(std::vector<Bullet*>& vec)
{
	auto it = vec.begin();
	while (it != vec.end())
	{
		(*it)->removeFromParent();
		it = vec.erase(it);
	}
}

void BulletPattern::removeOutOfBoundsObjects(std::vector<Bullet*>& vec)
{
	auto iteratorBegin = vec.begin();
	auto iteratorEnd = vec.rbegin();

	while (iteratorBegin != iteratorEnd.base())
	{
		while (iteratorEnd.base() != vec.begin() && (*iteratorEnd)->isOutOfBounds())
		{
			(*iteratorEnd)->removeFromParent();
			iteratorEnd++;
		}
		while (iteratorBegin != vec.rbegin().base() && !(*iteratorBegin)->isOutOfBounds())
		{
			iteratorBegin++;
		}

		if (iteratorBegin != iteratorEnd.base())
		{
			std::iter_swap(iteratorBegin, iteratorEnd);
		}
	}

	vec.resize(std::distance(vec.begin(), iteratorBegin));
}
