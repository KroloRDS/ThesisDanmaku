#pragma once

#include "cocos2d.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	static Bullet* createBullet(std::string, cocos2d::Vec2);
	CREATE_FUNC(Bullet);
	void update(float);
	float getSpeed();
	void setSpeed(float);
	float getRot();
	void setRot(float);
private:
	float speed = 0.0f;
	float rotation = 0.0f;

	static cocos2d::PhysicsBody* createBody();
};
