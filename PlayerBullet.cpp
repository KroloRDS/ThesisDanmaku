#include "PlayerBullet.h"
#include "GameScene.h"

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
	isOutOfBounds();
}

void PlayerBullet::isOutOfBounds()
{
	if (absolutePos.x < GameScene::GAME_INNER_BOUNDS[0].x ||
		absolutePos.y < GameScene::GAME_INNER_BOUNDS[0].y ||
		absolutePos.x > GameScene::GAME_INNER_BOUNDS[2].x ||
		absolutePos.y > GameScene::GAME_INNER_BOUNDS[2].y)
	{
		safeToDelete = true;
	}
}
