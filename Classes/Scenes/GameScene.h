#pragma once

#include "cocos2d.h"
#include "GameOver.h"
#include "GameObjects/Player.h"
#include "BulletPatterns/BulletPattern00.h"

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
	BulletPattern00* pattern = nullptr;

	bool onContactBegin(cocos2d::PhysicsContact&);

	template <class T>
	void removeOutOfBoundsBullets(std::vector<T*>&);
};
