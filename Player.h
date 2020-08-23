#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "PlayerBullet.h"
#include "KeyboardManager.h"

class Player : public GameObject
{
public:
	static Player* createPlayer(std::string, cocos2d::Vec2);
	CREATE_FUNC(Player);
	void update(float) override;
	void setPos(cocos2d::Vec2);
	cocos2d::DrawNode* getHitbox();
private:
	bool focused = false;
	float nextBulletInterval = 0.0;
	cocos2d::DrawNode* hitbox = nullptr;
	cocos2d::Vector<PlayerBullet*> playerBullets = {};

	void move(float);
	void fire(float);
	void updateBullets(float);

	static const float FOCUSED_SPEED;
	static const float UNFOCUSED_SPEED;
	static const float HITBOX_RADIUS;
	static const float BULLET_INTERVAL;
};
