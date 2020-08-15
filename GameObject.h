#pragma once

#include "cocos2d.h"

class GameObject
{
public:
    GameObject(std::string str);
    cocos2d::Sprite* getSprite();
    virtual void update(float) abstract;
private:
    cocos2d::Sprite sprite;
};