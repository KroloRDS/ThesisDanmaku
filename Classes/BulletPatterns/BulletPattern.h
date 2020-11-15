#pragma once

#include "cocos2d.h"
#include "GameObjects/Bullet.h"
#include "GameObjects/Laser.h"
#include "GameObjects/Player.h"
#include "HelperClasses/PatternName.h"

class BulletPattern : public cocos2d::Node
{
public:
	std::vector<Bullet*>& getBullets();
	std::vector<Laser*>& getLasers();
	
	PatternName* getName();
	int getMaxHp();
	int getHp();
	
	void removeAllBullets();
	int damage();

protected:
	std::vector<Bullet*> bullets = {};
	std::vector<Laser*> lasers = {};

	PatternName* name = nullptr;
	Player* player = nullptr;

	cocos2d::Vec2 origin = cocos2d::Vec2(0, 0);
	int maxHp = 0;
	int hp = 0;

	void initPattern(cocos2d::Vec2, std::string, int);
	void updateBullets(float);

private:
	void removeAllObjects(std::vector<Bullet*>& vec);
	static void removeOutOfBoundsObjects(std::vector<Bullet*>& vec);
};
