#pragma once

#include "cocos2d.h"
#include "GameObjects/Bullet.h"
#include "GameObjects/Laser.h"

class BulletPattern : public cocos2d::Node
{
public:
    std::vector<Bullet*>& getBullets();
    std::vector<Laser*>& getLasers();
    void removeAllBullets();
    int getHp();
protected:
    void updateBullets(float);
    std::vector<Bullet*> bullets = {};
    std::vector<Laser*> lasers = {};
    int hp = 0;
private:
    void removeAllObjects(std::vector<Bullet*>& vec);
    static void removeOutOfBoundsObjects(std::vector<Bullet*>& vec);
};
