#pragma once

#include "cocos2d.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	static Bullet* createBullet(std::string, cocos2d::Vec2);
	CREATE_FUNC(Bullet);
	void update(float);
	double getSpeed();
	void setSpeed(double);
	double getRot();
	void setRot(double);
private:
	double speed = 0.0;
	double rotation = 0.0;
};
