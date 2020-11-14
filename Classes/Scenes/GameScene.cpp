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
	Settings::getHitboxOption() == Settings::HITBOXES::PLAYER_AND_BULLETS ?
		scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL) :
		scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_NONE);
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

	player = Player::createPlayer();
	addChild(player);

	enemy = Enemy::createEnemy(player);
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
	auto pos = cocos2d::Vec2(UI_TEXT_X_POS, UI_TEXT_Y_POS);
	std::vector<MyMenuItem*> uiElements;

	scoreLabel = MyMenuItem::createMenuItem("Score", UI_FONT_NAME, UI_FONT_SIZE);
	uiElements.push_back(scoreLabel);

	scoreCounter = MyMenuItem::createMenuItem("0", UI_FONT_NAME, UI_FONT_SIZE);
	uiElements.push_back(scoreCounter);

	livesLabel = MyMenuItem::createMenuItem("Player: " + std::to_string(Player::DEFAULT_LIVES), UI_FONT_NAME, UI_FONT_SIZE);
	uiElements.push_back(livesLabel);

	patternGrazeLabel = MyMenuItem::createMenuItem("Pattern Graze", UI_FONT_NAME, UI_FONT_SIZE);
	uiElements.push_back(patternGrazeLabel);

	patternGrazeCounter = MyMenuItem::createMenuItem("0", UI_FONT_NAME, UI_FONT_SIZE);
	uiElements.push_back(patternGrazeCounter);

	totalGrazeLabel = MyMenuItem::createMenuItem("Total Graze", UI_FONT_NAME, UI_FONT_SIZE);
	uiElements.push_back(totalGrazeLabel);

	totalGrazeCounter = MyMenuItem::createMenuItem("0", UI_FONT_NAME, UI_FONT_SIZE);
	uiElements.push_back(totalGrazeCounter);

	for (MyMenuItem* uiElement : uiElements)
	{
		uiElement->setLocalZOrder(2);
		uiElement->setPos(pos);
		uiElement->select();
		addChild(uiElement);

		pos.y -= UI_TEXT_Y_MARGIN;
	}
}

void GameScene::addOverlay()
{
	auto overlay = cocos2d::Sprite::create("overlay.png");
	auto sizeX = Settings::getWindowSizeX() / 2.0f;
	auto sizeY = Settings::getWindowSizeY() / 2.0f;
	overlay->setPosition(cocos2d::Vec2(sizeX, sizeY));
	overlay->setScale(Settings::getScale());
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
		patternGraze++;
		patternGrazeCounter->setText(std::to_string(patternGraze));

		totalGraze++;
		totalGrazeCounter->setText(std::to_string(totalGraze));

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
	noHitBonus = false;
	enemy->getBulletPattern()->removeAllBullets();
	livesLabel->setText("Player: " + std::to_string(player->getLives()));
}

void GameScene::update(float delta)
{
	if (pause)
	{
		pause = false;
		auto scene = PauseScene::createScene(takeScreenshot());
		cocos2d::Director::getInstance()->pushScene(scene);
	}

	for (Node* child : getChildren())
	{
		child->update(delta);
	}

	if (!enemy->isDefeated())
	{
		hitEnemy();
	}
	else if (enemy->getIFrames() <= 0.0f)
	{
		cocos2d::Director::getInstance()->replaceScene(GameOver::createScene("YOU WON"));
	}

	updateScoreCounter();
}

void GameScene::hitEnemy()
{
	std::vector<PlayerBullet*>& vec = player->getBullets();
	auto it = vec.begin();

	while (it != vec.end())
	{
		if ((*it)->getSpriteBoundingBox().intersectsRect(enemy->getSpriteBoundingBox()))
		{
			damageEnemy((*it)->getPos());
			(*it)->removeFromParent();
			it = vec.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GameScene::damageEnemy(cocos2d::Vec2 pos)
{
	pos.y += 50;
	auto gameObj = GameObject::createGameObject("damage.png", pos);
	auto dmgSprite = gameObj->getSprite();
	
	dmgSprite->setScale(Settings::getScale() * 1.5f);
	dmgSprite->setOpacity(150);
	addChild(gameObj);

	dmgSprite->runAction(cocos2d::FadeTo::create(0.3f, 0));

	if (enemy->getIFrames() > 0.0f)
	{
		return;
	}

	score += totalGraze + INIT_HIT_POINT_VALUE;

	if (enemy->damage() <= 0)
	{
		nextPattern();
	}
}

void GameScene::nextPattern()
{
	enemy->nextPattern();
	
	if (noHitBonus)
	{
		score += INIT_HIT_POINT_VALUE * patternGraze;
	}
	
	noHitBonus = true;
	patternGraze = 0;
	patternGrazeCounter->setText("0");
}

void GameScene::updateScoreCounter()
{
	int increaseAmount = INIT_HIT_POINT_VALUE;
	while (increaseAmount > 1)
	{
		if (displayScore + increaseAmount < score)
		{
			displayScore += increaseAmount;
			scoreCounter->setText(std::to_string(displayScore));
			return;
		}
		increaseAmount /= 10;
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
