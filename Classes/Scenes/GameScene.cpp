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

const cocos2d::Vec2 GameScene::PLAYER_INIT_POS = cocos2d::Vec2(440, 300);
const cocos2d::Vec2 GameScene::ENEMY_INIT_POS = cocos2d::Vec2(440, 600);

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

	addListeners();
	addChild(createOverlay());

	player = Player::createPlayer("reimu.png", PLAYER_INIT_POS);
	addChild(player);

	enemy = Enemy::createEnemy("yukari.png", ENEMY_INIT_POS);
	addChild(enemy);

	scheduleUpdate();
	return true;
}

void GameScene::addListeners()
{
	auto keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::pressKey, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::releaseKey, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	
	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

cocos2d::Sprite* GameScene::createOverlay()
{
	auto overlay = cocos2d::Sprite::create("overlay.png");
	overlay->setScale(Settings::getScale());
	overlay->setPosition(cocos2d::Vec2(Settings::getWindowSizeX() * 0.5f, Settings::getWindowSizeY() * 0.5f));
	overlay->setGlobalZOrder(1.0f);
	return overlay;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		//cocos2d::Director::getInstance()->replaceScene(GameOver::createScene("GAME OVER"));
	}

	return true;
}

void GameScene::pressKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	KeyboardManager::pressKey(keyCode);
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		auto scene = PauseScene::createScene(takeScreenshot());
		scene->addChild(createOverlay());
		cocos2d::Director::getInstance()->pushScene(scene);
	}
}

void GameScene::releaseKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	KeyboardManager::releaseKey(keyCode);
}

void GameScene::update(float delta)
{
	hitEnemy(player->getBullets());
	removeOutOfBoundsBullets(player->getBullets());
	removeOutOfBoundsBullets(enemy->getBullets());
	
	for (Node* child : getChildren())
	{
		child->update(delta);
	}

	if (enemy->getHp() <= 0)
	{
		cocos2d::Director::getInstance()->replaceScene(GameOver::createScene("YOU WON"));
	}
}

cocos2d::RenderTexture* GameScene::takeScreenshot()
{
	removeOutOfBoundsBullets(player->getBullets());
	removeOutOfBoundsBullets(enemy->getBullets());

	cocos2d::RenderTexture* rt = cocos2d::RenderTexture::create(Settings::getWindowSizeX(), Settings::getWindowSizeY());
	rt->begin();
	visit();
	rt->end();
	rt->getSprite()->setAnchorPoint(cocos2d::Vec2(0, 0));

	return rt;
}

void GameScene::hitEnemy(std::vector<PlayerBullet*>& vec)
{
	auto it = vec.begin();
	while (it != vec.end())
	{
		if ((*it)->getSpriteBoundingBox().intersectsRect(enemy->getSpriteBoundingBox()))
		{
			enemy->damage();
			(*it)->removeFromParent();
			it = vec.erase(it);
		}
		else
		{
			++it;
		}
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
