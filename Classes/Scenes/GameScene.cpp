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

	addOverlay();
	addUIElements();
	addListeners();

	int seed = cocos2d::RandomHelper::random_int(0, RAND_MAX);
	std::srand(seed);

	player = Player::createPlayer("reimu.png");
	addChild(player);

	enemy = Enemy::createEnemy("yukari.png", ENEMY_INIT_POS, player);
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

void GameScene::addUIElements()
{
	grazeLabel = MyMenuItem::createMenuItem("Graze", "fonts/arial.ttf", 50.0f);
	grazeLabel->setPos(cocos2d::Vec2(950, 600));
	grazeLabel->setLocalZOrder(2);
	grazeLabel->select();
	addChild(grazeLabel);

	grazeCounter = MyMenuItem::createMenuItem("0", "fonts/arial.ttf", 50.0f);
	grazeCounter->setPos(cocos2d::Vec2(950, 540));
	grazeCounter->setLocalZOrder(2);
	grazeCounter->select();
	addChild(grazeCounter);

	livesLabel = MyMenuItem::createMenuItem("Player: " + std::to_string(Player::DEFAULT_LIVES), "fonts/arial.ttf", 50.0f);
	livesLabel->setPos(cocos2d::Vec2(955, 700));
	livesLabel->setLocalZOrder(2);
	livesLabel->select();
	addChild(livesLabel);
}

void GameScene::addOverlay()
{
	auto overlay = cocos2d::Sprite::create("overlay.png");
	overlay->setScale(Settings::getScale());
	overlay->setPosition(cocos2d::Vec2(Settings::getWindowSizeX() * 0.5f, Settings::getWindowSizeY() * 0.5f));
	overlay->setLocalZOrder(1);
	addChild(overlay);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA && bodyB)
	{
		onContact(bodyA, bodyB);
	}

	return true;
}

void GameScene::pressKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	KeyboardManager::pressKey(keyCode);
	pause = keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE;
}

void GameScene::releaseKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	KeyboardManager::releaseKey(keyCode);
}

void GameScene::onContact(cocos2d::PhysicsBody* bodyA, cocos2d::PhysicsBody* bodyB)
{
	if (bodyA->getCategoryBitmask() == 0x4 || bodyB->getCategoryBitmask() == 0x4)
	{
		graze++;
		grazeCounter->setText(std::to_string(graze));
		return;
	}

	//if (player->getIFrames() > 0.0f)
	{
		return;
	}

	if (player->getLives() == 0)
	{
		cocos2d::Director::getInstance()->replaceScene(GameOver::createScene("GAME OVER"));
		return;
	}

	player->kill();
	livesLabel->setText("Player: " + std::to_string(player->getLives()));
	enemy->getBulletPattern()->removeAllBullets();
}

void GameScene::update(float delta)
{
	for (Node* child : getChildren())
	{
		child->update(delta);
	}

	if (enemy->isDefeated())
	{
		cocos2d::Director::getInstance()->replaceScene(GameOver::createScene("YOU WON"));
	}

	if (pause)
	{
		pause = false;
		auto scene = PauseScene::createScene(takeScreenshot());
		cocos2d::Director::getInstance()->pushScene(scene);
	}
}

cocos2d::RenderTexture* GameScene::takeScreenshot()
{
	cocos2d::RenderTexture* rt = cocos2d::RenderTexture::create((int)Settings::getWindowSizeX(), (int)Settings::getWindowSizeY());
	rt->getSprite()->setAnchorPoint(cocos2d::Vec2(0, 0));

	rt->begin();
	visit();
	rt->end();

	return rt;
}
