#pragma once

#include "cocos2d.h"
#include "HelperClasses/Settings.h"
#include "HelperClasses/SpriteRepository.h"

class GameObject : public cocos2d::Node
{
public:
	static GameObject* createGameObject(SpriteRepository::SPRITE, cocos2d::Vec2);
	void initGameObj(SpriteRepository::SPRITE, cocos2d::Vec2);
	CREATE_FUNC(GameObject);

	void setPos(cocos2d::Vec2);
	cocos2d::Vec2 getPos();
	cocos2d::Rect getSpriteBoundingBox();

	cocos2d::Sprite* getSprite();
	bool isOutOfBounds();
	bool isOutOfInnerBounds();
protected:
	cocos2d::Sprite* sprite = nullptr;
	cocos2d::Vec2 absolutePos = cocos2d::Vec2(0, 0);
};
