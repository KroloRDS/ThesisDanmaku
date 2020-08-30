#include "GameScene.h"

const float GameScene::BULLET_INTERVAL = 0.06;
const float GameScene::BULLET_SPEED = 500.0;
const float GameScene::MAX_ROTATION_SPEED = 5.0;

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

	this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	SpellCard1(delta);
	player->update(delta);
}

void GameScene::SpellCard1(float delta)
{
	if (nextBulletInterval > 0.0)
	{
		nextBulletInterval -= delta;
	}
	else
	{
		for (int i = 0; i < ARMS_COUNT; i++)
		{
			bullets.pushBack(Bullet::createBullet("bullet.png", cocos2d::Vec2(440, 600)));
			bullets.back()->setSpeed(BULLET_SPEED);
			bullets.back()->setRot(rotation + i * 360.0 / ARMS_COUNT);
			addChild(bullets.back());
		}
		nextBulletInterval += BULLET_INTERVAL;
	}
	
	cocos2d::Vector<Bullet*> bulletsToKeep = {};
	for (Bullet* bullet : bullets)
	{
		if (bullet->isOutOfBounds())
		{
			bullet->removeFromParent();
		}
		else
		{
			bulletsToKeep.pushBack(bullet);
			bullet->update(delta);
		}
	}
	bullets = bulletsToKeep;

	rotationSpeed += acceleration;
	rotation += rotationSpeed;
	rotation = fmod(rotation, 360.0);

	if (abs(rotationSpeed) > MAX_ROTATION_SPEED)
	{
		acceleration *= -1;
	}
}
