#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "PlayerBullet.h"
#include "HelperClasses/KeyboardManager.h"

class Player : public GameObject
{
public:
	static Player* createPlayer(std::string);
	CREATE_FUNC(Player);
	void update(float);
	void setPos(cocos2d::Vec2);
	void kill();
	int getLives();
	float getIFrames();
	std::vector<PlayerBullet*>& getBullets();

	static const int DEFAULT_LIVES = 2;

private:
	int lives = 0;
	bool focused = false;
	float iFrames = 0.0f;
	float nextBulletInterval = 0.0f;
	std::vector<PlayerBullet*> playerBullets = {};

	cocos2d::Node* hitbox = nullptr;
	cocos2d::Node* grazeHitbox = nullptr;

	static cocos2d::Node* createHitbox();
	static cocos2d::Node* createGrazeHitbox();
	void move(float);
	void fire(float);
	void updateIFrames(float);

	void removeAllObjects(std::vector<PlayerBullet*>& vec);
	static void removeOutOfBoundsObjects(std::vector<PlayerBullet*>& vec);

	static const float IFRAMES_AFTER_DEATH;
	static const float FOCUSED_SPEED;
	static const float UNFOCUSED_SPEED;
	static const float HITBOX_RADIUS;
	static const float GRAZE_HITBOX_RADIUS;
	static const float BULLET_INTERVAL;
	static const float DIAGONAL_COEFFICIENT;
	static const float GAME_BOUNDS_OFFSET;
	static const float BULLET_X_OFFSET;
	static const float BULLET_Y_OFFSET;
	static const cocos2d::Vec2 INIT_POS;
};
