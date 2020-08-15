#include "MovingSprite.h"

bool movingLeft;
bool movingRight;
bool movingUp;
bool movingDown;

cocos2d::Scene* MovingSprite::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = MovingSprite::create();
	scene->addChild(layer);
	return scene;
}

bool MovingSprite::init()
{
	if (!Layer::init())
	{
		return false;
	}

	movingLeft = false;
	movingRight = false;
	movingUp = false;
	movingDown = false;

	sprite = cocos2d::Sprite::create("HelloWorld.png");
	sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
	this->addChild(sprite, 0);
	
	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			movingLeft = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			movingRight = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			movingUp = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			movingDown = true;
			break;
		}
	};

	eventListener->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			movingLeft = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			movingRight = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			movingUp = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			movingDown = false;
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);

	this->scheduleUpdate();
	return true;
}

void MovingSprite::update(float delta)
{
	auto position = sprite->getPosition();
	int speed = 100;
	
	if (movingLeft)
		position.x -= speed * delta;
	if (movingRight)
		position.x += speed * delta;
	if (movingUp)
		position.y += speed * delta;
	if (movingDown)
		position.y -= speed * delta;
	
	sprite->setPosition(position);
}