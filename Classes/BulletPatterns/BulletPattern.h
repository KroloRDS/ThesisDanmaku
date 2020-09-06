#pragma once

#include "cocos2d.h"
#include "GameObjects/Bullet.h"

class BulletPattern : public cocos2d::Node
{
public:
    std::vector<Bullet*>& getBullets();
protected:
    void updateBullets(float);
    std::vector<Bullet*> bullets = {};
};
