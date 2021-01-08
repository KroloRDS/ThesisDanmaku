#include "SpriteRepository.h"

bool SpriteRepository::initialized = false;
cocos2d::Sprite* SpriteRepository::arrowhead = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::bubble = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::butterlfy = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::damage = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::enemy = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::enemyIndicator = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::focus = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::hitbox = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::laser = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::mentos = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::normalBullet = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::overlay = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::player = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::playerBullet = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::spawn = new cocos2d::Sprite();
cocos2d::Sprite* SpriteRepository::testBullet = new cocos2d::Sprite();

void SpriteRepository::init()
{
	if (initialized)
	{
		return;
	}

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");
	
	arrowhead->initWithSpriteFrameName("arrowhead");
	bubble->initWithSpriteFrameName("bubble");
	butterlfy->initWithSpriteFrameName("butterfly");
	damage->initWithSpriteFrameName("damage");
	enemy->initWithSpriteFrameName("enemy");
	enemyIndicator->initWithSpriteFrameName("enemy_indicator");
	focus->initWithSpriteFrameName("focus");
	hitbox->initWithSpriteFrameName("hitbox");
	laser->initWithSpriteFrameName("laser");
	mentos->initWithSpriteFrameName("mentos");
	normalBullet->initWithSpriteFrameName("normal_bullet");
	overlay->initWithSpriteFrameName("overlay");
	player->initWithSpriteFrameName("player");
	playerBullet->initWithSpriteFrameName("player_bullet");
	spawn->initWithSpriteFrameName("spawn");
	testBullet->initWithSpriteFrameName("test_bullet");

	initialized = true;
}

cocos2d::Sprite* SpriteRepository::getSprite(SPRITE sprite)
{
	switch (sprite)
	{
	case ARROWHEAD:
		return cocos2d::Sprite::createWithSpriteFrame(arrowhead->getSpriteFrame());
	case BUBBLE:
		return cocos2d::Sprite::createWithSpriteFrame(bubble->getSpriteFrame());
	case BUTTERFLY:
		return cocos2d::Sprite::createWithSpriteFrame(butterlfy->getSpriteFrame());
	case DAMAGE:
		return cocos2d::Sprite::createWithSpriteFrame(damage->getSpriteFrame());
	case ENEMY:
		return cocos2d::Sprite::createWithSpriteFrame(enemy->getSpriteFrame());
	case ENEMY_INDICATOR:
		return cocos2d::Sprite::createWithSpriteFrame(enemyIndicator->getSpriteFrame());
	case FOCUS:
		return cocos2d::Sprite::createWithSpriteFrame(focus->getSpriteFrame());
	case HITBOX:
		return cocos2d::Sprite::createWithSpriteFrame(hitbox->getSpriteFrame());
	case LASER:
		return cocos2d::Sprite::createWithSpriteFrame(laser->getSpriteFrame());
	case MENTOS:
		return cocos2d::Sprite::createWithSpriteFrame(mentos->getSpriteFrame());
	case NORMAL_BULLET:
		return cocos2d::Sprite::createWithSpriteFrame(normalBullet->getSpriteFrame());
	case OVERLAY:
		return cocos2d::Sprite::createWithSpriteFrame(overlay->getSpriteFrame());
	case PLAYER:
		return cocos2d::Sprite::createWithSpriteFrame(player->getSpriteFrame());
	case PLAYER_BULLET:
		return cocos2d::Sprite::createWithSpriteFrame(playerBullet->getSpriteFrame());
	case SPAWN:
		return cocos2d::Sprite::createWithSpriteFrame(spawn->getSpriteFrame());
	case TEST_BULLET:
		return cocos2d::Sprite::createWithSpriteFrame(testBullet->getSpriteFrame());
	default:
		return nullptr;
	}
}
