#pragma once

#include "cocos2d.h"
#include "Settings.h"

class GameObject : public cocos2d::Node
{
public:
    static GameObject* createGameObject(std::string, cocos2d::Vec2);
    CREATE_FUNC(GameObject);
    void initGameObj(std::string, cocos2d::Vec2);
    cocos2d::Sprite* getSprite();
    void setPos(cocos2d::Vec2);
    cocos2d::Vec2 getPos();
    bool isOutOfBounds();
protected:
    cocos2d::Sprite* sprite = nullptr;
    cocos2d::Vec2 absolutePos = cocos2d::Vec2(0, 0);
    bool safeToDelete = false;
};
