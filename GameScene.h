#pragma once

#include "cocos2d.h"
#include "Player.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(GameScene);
	void update(float) override;

	static const cocos2d::Vec2 GAME_BOUNDS[4];

private:
	std::vector<GameObject*> gameObjects;
	Player* player;
};