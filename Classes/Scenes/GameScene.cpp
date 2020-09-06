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

	player = Player::createPlayer("reimu.png", cocos2d::Vec2(440, 300));
	addChild(player);

	pattern = BulletPattern00::createBulletPattern00();
	addChild(pattern);

	this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	pattern->update(delta);
	player->update(delta);
	removeUnusedObjects(player->getBullets());
	removeUnusedObjects(pattern->getBullets());
}

template <class T>
void GameScene::removeUnusedObjects(std::vector<T*>& vec)
{
	auto iteratorBegin = vec.begin();
	auto iteratorEnd = vec.rbegin();

	while (iteratorBegin != iteratorEnd.base())
	{
		while (iteratorEnd.base() != vec.begin() && (*iteratorEnd)->isOutOfBounds())
		{
			(*iteratorEnd)->removeFromParent();
			iteratorEnd++;
		}
		while (iteratorBegin != vec.rbegin().base() && !(*iteratorBegin)->isOutOfBounds())
		{
			iteratorBegin++;
		}

		if (iteratorBegin != iteratorEnd.base())
		{
			std::iter_swap(iteratorBegin, iteratorEnd);
		}
	}

	vec.resize(std::distance(vec.begin(), iteratorBegin));
}
