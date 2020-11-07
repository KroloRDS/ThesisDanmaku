#pragma once

#include "cocos2d.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	static Bullet* createBullet(int, cocos2d::Vec2);
	CREATE_FUNC(Bullet);
	void update(float);
	float getSpeed();
	void setSpeed(float);
	float getRot();
	void setRot(float);

	enum type { ARROWHEAD = 0, LASER_SEGMENT };

private:
	float speed = 0.0f;
	float rotation = 0.0f;
	float xRotationCoeff = 0.0f;
	float yRotationCoeff = 0.0f;

	std::string getSpriteName(int);
	void createHitbox(int);
	cocos2d::PhysicsBody* createArrowheadHitbox();
	cocos2d::PhysicsBody* createRectangularHitbox(float, float, float, float);
	cocos2d::PhysicsBody* createCircularHitbox(float);
};
