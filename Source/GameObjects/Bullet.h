#pragma once

#include "cocos2d.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	static Bullet* createBullet(cocos2d::Vec2, int type, int subtype = 0);
	CREATE_FUNC(Bullet);
	void update(float);
	
	float getSpeed();
	void setSpeed(float);
	
	float getRot();
	void setRot(float);

	int getSubtype();
	void setSubtype(int);
	
	int getType();
	float getAge();

	void aimAt(cocos2d::Vec2 target, float angle = 0.0f);

	enum type { TEST = 0, NORMAL, ARROWHEAD, BUTTERFLY, MENTOS, BUBBLE, LASER_SEGMENT };

private:
	float speed = 0.0f;
	float rotation = 0.0f;
	float xRotationCoeff = 0.0f;
	float yRotationCoeff = 0.0f;

	int type = 0;
	int subtype = 0;
	float age = 0.0f;

	cocos2d::Node* hitbox = nullptr;

	void spawnAnimation();

	SpriteRepository::SPRITE getSpriteType(int);
	void createHitbox(int);

	cocos2d::PhysicsBody* createTestHitbox();
	cocos2d::PhysicsBody* createArrowheadHitbox();
	cocos2d::PhysicsBody* createNormalBulletHitbox();
	cocos2d::PhysicsBody* createRectangularHitbox(float, float, float, float);
	cocos2d::PhysicsBody* createCircularHitbox(float);
};
