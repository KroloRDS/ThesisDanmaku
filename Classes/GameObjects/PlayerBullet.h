#pragma once

#include "cocos2d.h"
#include "GameObject.h"

class PlayerBullet : public GameObject
{
public:
	static PlayerBullet* createPlayerBullet(std::string, cocos2d::Vec2);
	CREATE_FUNC(PlayerBullet);
	void update(float);
private:
	static const float PLAYER_BULLET_SPEED;
};
