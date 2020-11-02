#pragma once

#include "cocos2d.h"
#include "GameOver.h"
#include "PauseScene.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"

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
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	
	MyMenuItem* grazeLabel = nullptr;
	MyMenuItem* grazeCounter = nullptr;
	int graze = 0;

	MyMenuItem* livesLabel = nullptr;

	static const cocos2d::Vec2 ENEMY_INIT_POS;

	void addListeners();
	void addUIElements();
	void addOverlay();
	
	bool onContactBegin(cocos2d::PhysicsContact&);
	void pressKey(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void releaseKey(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

	void onContact(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*);

	cocos2d::RenderTexture* takeScreenshot();
	bool pause = false;
};
