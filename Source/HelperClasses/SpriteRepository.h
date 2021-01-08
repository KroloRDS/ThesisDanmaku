#pragma once

#include "cocos2d.h"

class SpriteRepository
{
public:
	enum SPRITE
	{
		BLANK = 0,
		ARROWHEAD,
		BUBBLE,
		BUTTERFLY,
		DAMAGE,
		ENEMY,
		ENEMY_INDICATOR,
		FOCUS,
		HITBOX,
		LASER,
		MENTOS,
		NORMAL_BULLET,
		OVERLAY,
		PLAYER,
		PLAYER_BULLET,
		SPAWN,
		TEST_BULLET
	};

	static void init();
	static cocos2d::Sprite* getSprite(SPRITE);

private:
	static bool initialized;
	static cocos2d::Sprite* arrowhead;
	static cocos2d::Sprite* bubble;
	static cocos2d::Sprite* butterlfy;
	static cocos2d::Sprite* damage;
	static cocos2d::Sprite* enemy;
	static cocos2d::Sprite* enemyIndicator;
	static cocos2d::Sprite* focus;
	static cocos2d::Sprite* hitbox;
	static cocos2d::Sprite* laser;
	static cocos2d::Sprite* mentos;
	static cocos2d::Sprite* normalBullet;
	static cocos2d::Sprite* overlay;
	static cocos2d::Sprite* player;
	static cocos2d::Sprite* playerBullet;
	static cocos2d::Sprite* spawn;
	static cocos2d::Sprite* testBullet;
};

