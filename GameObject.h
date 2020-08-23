#pragma once

#include "cocos2d.h"
#include "Settings.h"

class GameObject : public cocos2d::Node
{
public:
    GameObject(std::string, cocos2d::Vec2);
    cocos2d::Sprite* getSprite();
    void setPos(cocos2d::Vec2);
    cocos2d::Vec2 getPos();
    virtual void update(float) abstract;
protected:
    cocos2d::Sprite* sprite;
    cocos2d::Vec2 absolutePos;
};