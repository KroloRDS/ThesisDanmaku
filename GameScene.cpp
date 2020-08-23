#include "GameScene.h"

const cocos2d::Vec2 GameScene::GAME_BOUNDS[4] = {
	cocos2d::Vec2(60,32),
	cocos2d::Vec2(60,928),
	cocos2d::Vec2(820,928),
	cocos2d::Vec2(820,32)
};

cocos2d::Scene* GameScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		KeyboardManager::pressKey(keyCode);
	};
	eventListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		KeyboardManager::releaseKey(keyCode);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	auto rectNode = cocos2d::DrawNode::create();
	cocos2d::Color4F white(1, 1, 1, 1);
	rectNode->drawPolygon(GAME_BOUNDS, 4, white, 1, white);
	this->addChild(rectNode);

	player = new Player("reimu.png", cocos2d::Vec2(500, 500));
	gameObjects.push_back(player);
	this->addChild(player);

	this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->update(delta);
	}
}