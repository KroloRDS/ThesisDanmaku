#include "Player.h"
#include "Scenes/GameScene.h"

const float Player::FOCUSED_SPEED = 150.0f;
const float Player::UNFOCUSED_SPEED = 300.0f;
const float Player::HITBOX_RADIUS = 6.0f;
const float Player::BULLET_INTERVAL = 0.06f;

Player* Player::createPlayer(std::string str, cocos2d::Vec2 pos)
{
	Player* ret = Player::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj(str, pos);
	ret->sprite->setPhysicsBody(createBody());

	return ret;
}

cocos2d::PhysicsBody* Player::createBody()
{
	auto body = cocos2d::PhysicsBody::createCircle(HITBOX_RADIUS * Settings::getScale());
	body->setDynamic(false);
	body->setCategoryBitmask(0x1);
	body->setContactTestBitmask(0x2);
	return body;
}

void Player::update(float delta)
{
	focused = KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_SHIFT);
	move(delta);
	fire(delta);
	
	for (Node* child : getChildren())
	{
		child->update(delta);
	}
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
	playerBullets.push_back(leftBullet);
	playerBullets.push_back(rightBullet);
	addChild(leftBullet);
	addChild(rightBullet);
	nextBulletInterval += BULLET_INTERVAL;
}

std::vector<PlayerBullet*>& Player::getBullets()
{
	return playerBullets;
}

void Player::setPos(cocos2d::Vec2 newPosition)
{
	absolutePos = newPosition;
	sprite->setPosition(newPosition * Settings::getScale());
}
