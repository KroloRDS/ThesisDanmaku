#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "PlayerBullet.h"
#include "HelperClasses/KeyboardManager.h"

class Player : public GameObject
{
public:
	static Player* createPlayer(std::string, cocos2d::Vec2);
	CREATE_FUNC(Player);
	void update(float);
	void setPos(cocos2d::Vec2);
	std::vector<PlayerBullet*>& getBullets();
private:
	bool focused = false;
	float nextBulletInterval = 0.0f;
	std::vector<PlayerBullet*> playerBullets = {};

	static cocos2d::PhysicsBody* createBody();
	void move(float);
	void fire(float);

	static const float FOCUSED_SPEED;
	static const float UNFOCUSED_SPEED;
	static const float HITBOX_RADIUS;
	static const float BULLET_INTERVAL;
	static const float DIAGONAL_COEFFICIENT;
	static const float SCREEN_BORDER_OFFSET;
	static const float BULLET_X_OFFSET;
	static const float BULLET_Y_OFFSET;
};
