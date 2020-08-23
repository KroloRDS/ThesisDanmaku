#include "Player.h"
#include "GameScene.h"

const float Player::FOCUSED_SPEED = 150.0;
const float Player::UNFOCUSED_SPEED = 300.0;
const float Player::HITBOX_RADIUS = 6.0;

Player::Player(std::string str, cocos2d::Vec2 pos) : GameObject(str, pos)
{
	hitbox = cocos2d::DrawNode::create();
	cocos2d::Color4F cyan(0, 1, 1, 1);
	hitbox->drawDot(cocos2d::Vec2(0, 0), HITBOX_RADIUS, cyan);
	hitbox->setContentSize(cocos2d::Size(HITBOX_RADIUS * 2, HITBOX_RADIUS * 2));
	this->addChild(hitbox);
}

void Player::update(float delta)
{
	focused = KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_SHIFT);

	float speed = UNFOCUSED_SPEED;
	if (focused)
	{
		speed = FOCUSED_SPEED;
	}
	
	auto newPosition = getPos();
	auto radius = hitbox->getContentSize().width / 2;
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) &&
		newPosition.y + radius <= GameScene::GAME_BOUNDS[2].y)
	{
		newPosition.y += delta * speed;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) &&
		newPosition.y - radius >= GameScene::GAME_BOUNDS[0].y)
	{
		newPosition.y -= delta * speed;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) &&
		newPosition.x - radius >= GameScene::GAME_BOUNDS[0].x)
	{
		newPosition.x -= delta * speed;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) &&
		newPosition.x + radius <= GameScene::GAME_BOUNDS[2].x)
	{
		newPosition.x += delta * speed;
	}

	/*
	if (newPosition.x + radius <= GameScene::GAME_BOUNDS[0].x)
	{
		newPosition.x = GameScene::GAME_BOUNDS[0].x + radius;
	}
	
	if (playerPos.x + radius > GAME_BOUNDS[3].x)
	{
		playerPos.x = GAME_BOUNDS[0].x + radius;
	}
	if (playerPos.y - radius < GAME_BOUNDS[0].y)
	{
		playerPos.y = GAME_BOUNDS[0].y - radius;
	}
	if (playerPos.y + radius > GAME_BOUNDS[3].y)
	{
		playerPos.y = GAME_BOUNDS[0].y + radius;
	}
	*/
	setPos(newPosition);
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