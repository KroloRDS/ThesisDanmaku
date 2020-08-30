#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Bullet.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(GameScene);
	void update(float) override;

	static const cocos2d::Vec2 GAME_INNER_BOUNDS[4];
	static const cocos2d::Vec2 GAME_OUTER_BOUNDS[4];

private:
	cocos2d::Vector<Bullet*> bullets = {};
	Player* player = nullptr;

	void SpellCard1(float);

	static const int ARMS_COUNT = 8;
	static const float BULLET_INTERVAL;
	static const float BULLET_SPEED;
	static const float MAX_ROTATION_SPEED;
	
	float nextBulletInterval = 0.0;
	float rotation = 0.0;
	float rotationSpeed = 0.0;
	float acceleration = 0.02;
};
