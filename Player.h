#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "KeyboardManager.h"

class Player : public GameObject
{
public:
	Player(std::string, cocos2d::Vec2);
	void setPos(cocos2d::Vec2);
	void update(float) override;
	cocos2d::DrawNode* getHitbox();
private:
	bool focused;
	cocos2d::DrawNode* hitbox;

	static const float FOCUSED_SPEED;
	static const float UNFOCUSED_SPEED;
	static const float HITBOX_RADIUS;
};