#include "PlayerBullet.h"

const float PlayerBullet::PLAYER_BULLET_SPEED = 1000.0;

PlayerBullet* PlayerBullet::createPlayerBullet(std::string str, cocos2d::Vec2 pos)
{
	PlayerBullet* ret = PlayerBullet::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj(str, pos);
	return ret;
}

void PlayerBullet::update(float delta)
{
	auto newPosition = absolutePos;
	newPosition.y += delta * PLAYER_BULLET_SPEED;
	setPos(newPosition);
}
