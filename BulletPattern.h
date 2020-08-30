#pragma once

#include "cocos2d.h"
#include "Bullet.h"

class BulletPattern : public cocos2d::Node
{
protected:
    void updateBullets(float);
    cocos2d::Vector<Bullet*> bullets = {};
};
