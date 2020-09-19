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
	auto scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(Settings::getHitboxOption());
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

	auto keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		KeyboardManager::pressKey(keyCode);
	};
	keyboardListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		KeyboardManager::releaseKey(keyCode);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto rectNode = cocos2d::DrawNode::create();
	cocos2d::Color4F white(1, 1, 1, 1);
	rectNode->drawPolygon(GAME_INNER_BOUNDS, 4, white, 1, white);
	rectNode->setScale(Settings::getScale());
	addChild(rectNode);

	player = Player::createPlayer("reimu.png", cocos2d::Vec2(440, 300));
	addChild(player);

	pattern = BulletPattern00::createBulletPattern00();
	addChild(pattern);

	scheduleUpdate();
	return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		cocos2d::Director::getInstance()->replaceScene(GameOver::createScene());
	}

	return true;
}

void GameScene::update(float delta)
{
	removeOutOfBoundsBullets(player->getBullets());
	removeOutOfBoundsBullets(pattern->getBullets());

	for (Node* child : getChildren())
	{
		child->update(delta);
	}
}

template <class T>
void GameScene::removeOutOfBoundsBullets(std::vector<T*>& vec)
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
