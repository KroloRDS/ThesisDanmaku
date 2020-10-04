#include "Player.h"
#include "Scenes/GameScene.h"

const float Player::FOCUSED_SPEED = 200.0f;
const float Player::UNFOCUSED_SPEED = 400.0f;
const float Player::HITBOX_RADIUS = 6.0f;
const float Player::BULLET_INTERVAL = 0.06f;
const float Player::DIAGONAL_COEFFICIENT = 1.0f / sqrt(2.0f);
const float Player::SCREEN_BORDER_OFFSET = HITBOX_RADIUS * Settings::getScale() * 1.5f;
const float Player::BULLET_X_OFFSET = HITBOX_RADIUS * Settings::getScale() * 2.0f;
const float Player::BULLET_Y_OFFSET = HITBOX_RADIUS * Settings::getScale() * 7.0f;

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
	int verticalMovement = 0;
	int horizontalMovement = 0;
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) &&
		absolutePos.y + SCREEN_BORDER_OFFSET <= GameScene::GAME_INNER_BOUNDS[2].y)
	{
		verticalMovement++;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) &&
		absolutePos.y - SCREEN_BORDER_OFFSET >= GameScene::GAME_INNER_BOUNDS[0].y)
	{
		verticalMovement--;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) &&
		absolutePos.x - SCREEN_BORDER_OFFSET >= GameScene::GAME_INNER_BOUNDS[0].x)
	{
		horizontalMovement--;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) &&
		absolutePos.x + SCREEN_BORDER_OFFSET <= GameScene::GAME_INNER_BOUNDS[2].x)
	{
		horizontalMovement++;
	}

	float speed;
	focused ? speed = FOCUSED_SPEED : speed = UNFOCUSED_SPEED;
	
	int newX = horizontalMovement * speed;
	int newY = verticalMovement * speed;
	verticalMovement == 0 ? newX = (int)(newX * delta) : newX = (int)(newX * delta * DIAGONAL_COEFFICIENT);
	horizontalMovement == 0 ? newY = (int)(newY * delta) : newY = (int)(newY * delta * DIAGONAL_COEFFICIENT);
	
	auto newPosition = absolutePos;
	newPosition.x += newX;
	newPosition.y += newY;

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
	
	auto leftPos = absolutePos;
	auto rightPos = absolutePos;
	leftPos.x -= BULLET_X_OFFSET;
	rightPos.x += BULLET_X_OFFSET;
	leftPos.y += BULLET_Y_OFFSET;
	rightPos.y += BULLET_Y_OFFSET;
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
