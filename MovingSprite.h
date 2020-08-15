#pragma once

#include "cocos2d.h"

class MovingSprite : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(MovingSprite);

	void update(float) override;

private:
	cocos2d::Sprite* sprite;
};