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
	void removeAllBullets();
	int getHp();
	PatternName* getName();
protected:
	void updateBullets(float);
	
	std::vector<Bullet*> bullets = {};
	std::vector<Laser*> lasers = {};

	Player* player = nullptr;
	PatternName* name = nullptr;

	int hp = 0;
private:
	void removeAllObjects(std::vector<Bullet*>& vec);
	static void removeOutOfBoundsObjects(std::vector<Bullet*>& vec);
};
