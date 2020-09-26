#pragma once

#include "cocos2d.h"
#include "HelperClasses/Settings.h"

class GameObject : public cocos2d::Node
{
public:
	static GameObject* createGameObject(std::string, cocos2d::Vec2);
	void initGameObj(std::string, cocos2d::Vec2);
	CREATE_FUNC(GameObject);
	
	void setPos(cocos2d::Vec2);
	cocos2d::Vec2 getPos();
	cocos2d::Rect getSpriteBoundingBox();

	cocos2d::Sprite* getSprite();
	bool isOutOfBounds();
protected:
	cocos2d::Sprite* sprite = nullptr;
	cocos2d::Vec2 absolutePos = cocos2d::Vec2(0, 0);
};
