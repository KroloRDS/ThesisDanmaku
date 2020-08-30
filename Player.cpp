#include "Player.h"
#include "GameScene.h"

const float Player::FOCUSED_SPEED = 150.0;
const float Player::UNFOCUSED_SPEED = 300.0;
const float Player::HITBOX_RADIUS = 6.0;
const float Player::BULLET_INTERVAL = 0.06;

Player* Player::createPlayer(std::string str, cocos2d::Vec2 pos)
{
	Player* ret = Player::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj(str, pos);
	ret->hitbox = cocos2d::DrawNode::create();
	cocos2d::Color4F cyan(0, 1, 1, 1);
	ret->hitbox->drawDot(cocos2d::Vec2(0, 0), HITBOX_RADIUS * Settings::getScale(), cyan);
	ret->addChild(ret->hitbox);
	return ret;
}

void Player::update(float delta)
{
	focused = KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_SHIFT);
	move(delta);
	fire(delta);
	updateBullets(delta);
}

void Player::move(float delta)
{
	float speed = UNFOCUSED_SPEED;
	if (focused)
	{
		speed = FOCUSED_SPEED;
	}

	auto newPosition = absolutePos;
	auto radius = HITBOX_RADIUS * Settings::getScale();
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) &&
		newPosition.y + radius <= GameScene::GAME_INNER_BOUNDS[2].y)
	{
		newPosition.y += delta * speed;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) &&
		newPosition.y - radius >= GameScene::GAME_INNER_BOUNDS[0].y)
	{
		newPosition.y -= delta * speed;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) &&
		newPosition.x - radius >= GameScene::GAME_INNER_BOUNDS[0].x)
	{
		newPosition.x -= delta * speed;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) &&
		newPosition.x + radius <= GameScene::GAME_INNER_BOUNDS[2].x)
	{
		newPosition.x += delta * speed;
	}

	setPos(newPosition);
}

void Player::fire(float delta)
{
	if (!KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_Z))
	{
		return;
	}

	if (nextBulletInterval > 0.0)
	{
		nextBulletInterval -= delta;
		return;
	}
	
	auto radius = HITBOX_RADIUS * Settings::getScale();
	auto leftPos = absolutePos;
	auto rightPos = absolutePos;
	leftPos.x -= radius * 2;
	rightPos.x += radius * 2;
	leftPos.y += radius * 7;
	rightPos.y += radius * 7;
	auto leftBullet = PlayerBullet::createPlayerBullet("player_bullet.png", leftPos);
	auto rightBullet = PlayerBullet::createPlayerBullet("player_bullet.png", rightPos);
	playerBullets.pushBack(leftBullet);
	playerBullets.pushBack(rightBullet);
	addChild(leftBullet);
	addChild(rightBullet);
	nextBulletInterval += BULLET_INTERVAL;
}

void Player::updateBullets(float delta)
{
	cocos2d::Vector<PlayerBullet*> bulletsToKeep = {};
	for (PlayerBullet* bullet : playerBullets)
	{
		if (bullet->isOutOfBounds())
		{
			bullet->removeFromParent();
		}
		else
		{
			bulletsToKeep.pushBack(bullet);
			bullet->update(delta);
		}
	}
	playerBullets = bulletsToKeep;
}

cocos2d::DrawNode* Player::getHitbox()
{
	return hitbox;
}

void Player::setPos(cocos2d::Vec2 newPosition)
{
	absolutePos = newPosition;
	sprite->setPosition(newPosition * Settings::getScale());
	hitbox->setPosition(newPosition * Settings::getScale());
}
