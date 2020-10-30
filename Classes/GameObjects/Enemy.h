#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "EnemyHpBar.h"
#include "BulletPatterns/BulletPattern00.h"

class Enemy : public GameObject
{
public:
	static Enemy* createEnemy(std::string, cocos2d::Vec2);
	CREATE_FUNC(Enemy);
	void update(float);
	std::vector<Bullet*>& getBullets();
	
	int getHp();
	int getMaxHp();
	void damage(int damage = 1);
private:
	BulletPattern* bulletPattern = nullptr;
	EnemyHpBar* hpBar = nullptr;
	int hp = 0;
};
