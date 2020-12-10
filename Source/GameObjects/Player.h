#pragma once

#include "cocos2d.h"
#include "GameObject.h"
#include "PlayerBullet.h"
#include "HelperClasses/KeyboardManager.h"

class Player : public GameObject
{
public:
	static Player* createPlayer();
	CREATE_FUNC(Player);
	void update(float);
	void setPos(cocos2d::Vec2);
	void kill();
	int getLives();
	float getIFrames();
	GameObject* getHitboxSprite();
	std::vector<PlayerBullet*>& getBullets();

private:
	int lives = 0;
	bool focused = false;
	float iFrames = 0.0f;
	float nextBulletInterval = 0.0f;
	std::vector<PlayerBullet*> playerBullets = {};

	cocos2d::Node* hitbox = nullptr;
	cocos2d::Node* grazeHitbox = nullptr;
	GameObject* hitboxSprite = nullptr;
	GameObject* focusSprite = nullptr;

	void createHitbox();
	void createGrazeHitbox();
	void move(float);
	void fire(float);
	void updateIFrames(float);

	void removeAllObjects(std::vector<PlayerBullet*>& vec);
	static void removeOutOfBoundsObjects(std::vector<PlayerBullet*>& vec);

	const int DEFAULT_LIVES = 2;
	const float IFRAMES_AFTER_DEATH = 5.0f;
	const float FOCUSED_SPEED = 200.0f;
	const float UNFOCUSED_SPEED = 400.0f;
	const float HITBOX_RADIUS = 6.0f;
	const float GRAZE_HITBOX_RADIUS = 30.0f;
	const float BULLET_INTERVAL = 0.06f;
	const float FOCUS_SPRITE_ROTATION_SPEED = 30.0f;
	const float DIAGONAL_COEFFICIENT = 1.0f / sqrt(2.0f);
	const float GAME_BOUNDS_OFFSET = HITBOX_RADIUS * Settings::getScale() * 1.5f;
	const cocos2d::Vec2 INIT_POS = cocos2d::Vec2(440, 300);
	const cocos2d::Vec2 LEFT_BULLET_OFFSET = cocos2d::Vec2(12.0f, 40.0f);
	const cocos2d::Vec2 RIGHT_BULLET_OFFSET = cocos2d::Vec2(-12.0f, 40.0f);
};
