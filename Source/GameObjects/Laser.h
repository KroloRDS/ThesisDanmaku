#pragma once

#include "cocos2d.h"
#include "Bullet.h"

class Laser : public cocos2d::Node
{
public:
	static Laser* createLaser(cocos2d::Vec2, float);
	CREATE_FUNC(Laser);
	void update(float);

	void move(float, float);
	cocos2d::Vec2 getOrigin();

	void setRotation(float);
	float getRotation();

	std::vector<Bullet*>& getSegments();

private:
	cocos2d::Vec2 origin = cocos2d::Vec2(0, 0);
	std::vector<Bullet*> segments = {};

	cocos2d::Sprite* sprite = nullptr;

	float rotation = 0.0f;
	float nextSpawn = 0.0f;

	bool initialised = false;

	void createSprite();

	const int SEGMENT_OFFSET = 15;
	const float SEGMENT_SPAWN_RATE = 0.05f;
};

