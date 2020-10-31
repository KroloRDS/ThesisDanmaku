#include "Player.h"
#include "Scenes/GameScene.h"

const float Player::FOCUSED_SPEED = 200.0f;
const float Player::UNFOCUSED_SPEED = 400.0f;
const float Player::HITBOX_RADIUS = 6.0f;
const float Player::GRAZE_HITBOX_RADIUS = 24.0f;
const float Player::BULLET_INTERVAL = 0.06f;
const float Player::DIAGONAL_COEFFICIENT = 1.0f / sqrt(2.0f);
const float Player::GAME_BOUNDS_OFFSET = HITBOX_RADIUS * Settings::getScale() * 1.5f;
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
	ret->hitbox = createHitbox();
	ret->addChild(ret->hitbox);
	ret->grazeHitbox = createGrazeHitbox();
	ret->addChild(ret->grazeHitbox);

	return ret;
}

cocos2d::Node* Player::createHitbox()
{
	auto body = cocos2d::PhysicsBody::createCircle(HITBOX_RADIUS * Settings::getScale());
	body->setDynamic(false);
	body->setCategoryBitmask(0x1);
	body->setContactTestBitmask(0x2);

	auto node = cocos2d::Node::create();
	node->setPhysicsBody(body);

	return node;
}

cocos2d::Node* Player::createGrazeHitbox()
{
	auto body = cocos2d::PhysicsBody::createCircle(GRAZE_HITBOX_RADIUS * Settings::getScale());
	body->setDynamic(false);
	body->setCategoryBitmask(0x4);
	body->setContactTestBitmask(0x2);

	auto node = cocos2d::Node::create();
	node->setPhysicsBody(body);

	return node;
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
	int vDirection = 0;
	int hDirection = 0;
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) &&
		absolutePos.y + GAME_BOUNDS_OFFSET <= GameScene::GAME_INNER_BOUNDS[2].y)
	{
		vDirection++;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) &&
		absolutePos.y - GAME_BOUNDS_OFFSET >= GameScene::GAME_INNER_BOUNDS[0].y)
	{
		vDirection--;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) &&
		absolutePos.x - GAME_BOUNDS_OFFSET >= GameScene::GAME_INNER_BOUNDS[0].x)
	{
		hDirection--;
	}
	if (KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) &&
		absolutePos.x + GAME_BOUNDS_OFFSET <= GameScene::GAME_INNER_BOUNDS[2].x)
	{
		hDirection++;
	}

	auto newPosition = absolutePos;
	float distance = focused ? FOCUSED_SPEED * delta : UNFOCUSED_SPEED * delta;
	newPosition.x += (int)(hDirection * distance * (vDirection == 0 ? 1 : DIAGONAL_COEFFICIENT));
	newPosition.y += (int)(vDirection * distance * (hDirection == 0 ? 1 : DIAGONAL_COEFFICIENT));
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
	hitbox->setPosition(newPosition * Settings::getScale());
	grazeHitbox->setPosition(newPosition * Settings::getScale());
}
