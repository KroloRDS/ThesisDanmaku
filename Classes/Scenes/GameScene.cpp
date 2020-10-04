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

const cocos2d::Color4F GameScene::COLOR_WHITE = cocos2d::Color4F(1, 1, 1, 1);
const cocos2d::Vec2 GameScene::PLAYER_INIT_POS = cocos2d::Vec2(440, 300);
const cocos2d::Vec2 GameScene::ENEMY_INIT_POS = cocos2d::Vec2(440, 600);
const cocos2d::Vec2 GameScene::ENEMY_HP_BAR_POS = cocos2d::Vec2(GAME_INNER_BOUNDS[1].x + 50, GAME_INNER_BOUNDS[1].y - 50);

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
	addOverlay();

	enemyHpBar = cocos2d::DrawNode::create();
	addChild(enemyHpBar);

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

void GameScene::addOverlay()
{
	auto overlay = cocos2d::Sprite::create("overlay.png");
	overlay->setScale(Settings::getScale());
	overlay->setPosition(cocos2d::Vec2(Settings::getWindowSizeX() * 0.5f, Settings::getWindowSizeY() * 0.5f));
	overlay->setGlobalZOrder(1.0f);
	addChild(overlay);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		cocos2d::Director::getInstance()->replaceScene(GameOver::createScene("GAME OVER"));
	}

	return true;
}

void GameScene::pressKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	KeyboardManager::pressKey(keyCode);
}

void GameScene::releaseKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	KeyboardManager::releaseKey(keyCode);
}

void GameScene::update(float delta)
{
	updateEnemyHpBar();
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

void GameScene::updateEnemyHpBar()
{
	enemyHpBar->removeFromParent();
	enemyHpBar = cocos2d::DrawNode::create();
	enemyHpBar->setScale(Settings::getScale());
	addChild(enemyHpBar);
	
	int width = ENEMY_HP_BAR_MAX_WIDTH;
	width = (int)(width * static_cast<double>(enemy->getHp()) / static_cast<double>(enemy->getMaxHp()));
	cocos2d::Vec2 dest(ENEMY_HP_BAR_POS.x + width, ENEMY_HP_BAR_POS.y + ENEMY_HP_BAR_HEIGHT);
	enemyHpBar->drawSolidRect(ENEMY_HP_BAR_POS, dest, COLOR_WHITE);
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
