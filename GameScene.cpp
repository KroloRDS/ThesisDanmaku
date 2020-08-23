#include "GameScene.h"

const cocos2d::Vec2 GameScene::GAME_INNER_BOUNDS[4] = {
	cocos2d::Vec2(60, 32),
	cocos2d::Vec2(60, 928),
	cocos2d::Vec2(820, 928),
	cocos2d::Vec2(820, 32)
};

const cocos2d::Vec2 GameScene::GAME_OUTER_BOUNDS[4] = {
	cocos2d::Vec2(-140, -168),
	cocos2d::Vec2(-140, 1128),
	cocos2d::Vec2(1020, 1128),
	cocos2d::Vec2(1020, -168)
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
	rectNode->drawPolygon(GAME_INNER_BOUNDS, 4, white, 1, white);
	rectNode->setScale(Settings::getScale());
	addChild(rectNode);

	player = Player::createPlayer("reimu.png", cocos2d::Vec2(500, 500));
	gameObjects.pushBack(player);
	addChild(player);

	this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(), [&](GameObject* i) {return i->isSafeToDelete(); }), gameObjects.end());
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->update(delta);
	}
}
