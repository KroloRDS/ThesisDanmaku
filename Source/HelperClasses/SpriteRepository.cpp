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

	arrowhead->initWithFile("sprites/arrowhead.png");
	bubble->initWithFile("sprites/bubble.png");
	butterlfy->initWithFile("sprites/butterlfy.png");
	damage->initWithFile("sprites/damage.png");
	enemy->initWithFile("sprites/enemy.png");
	enemyIndicator->initWithFile("sprites/enemy_indicator.png");
	focus->initWithFile("sprites/focus.png");
	hitbox->initWithFile("sprites/hitbox.png");
	laser->initWithFile("sprites/laser.png");
	mentos->initWithFile("sprites/mentos.png");
	normalBullet->initWithFile("sprites/normal_bullet.png");
	overlay->initWithFile("sprites/overlay.png");
	player->initWithFile("sprites/player.png");
	playerBullet->initWithFile("sprites/playerBullet.png");
	spawn->initWithFile("sprites/spawn.png");
	testBullet->initWithFile("sprites/test_bullet.png");

	initialized = true;
}

cocos2d::Sprite* SpriteRepository::getSprite(SPRITE sprite)
{
	switch (sprite)
	{
	case ARROWHEAD:
		return cocos2d::Sprite::createWithTexture(arrowhead->getTexture());
	case BUBBLE:
		return cocos2d::Sprite::createWithTexture(bubble->getTexture());
	case BUTTERFLY:
		return cocos2d::Sprite::createWithTexture(butterlfy->getTexture());
	case DAMAGE:
		return cocos2d::Sprite::createWithTexture(damage->getTexture());
	case ENEMY:
		return cocos2d::Sprite::createWithTexture(enemy->getTexture());
	case ENEMY_INDICATOR:
		return cocos2d::Sprite::createWithTexture(enemyIndicator->getTexture());
	case FOCUS:
		return cocos2d::Sprite::createWithTexture(focus->getTexture());
	case HITBOX:
		return cocos2d::Sprite::createWithTexture(hitbox->getTexture());
	case LASER:
		return cocos2d::Sprite::createWithTexture(laser->getTexture());
	case MENTOS:
		return cocos2d::Sprite::createWithTexture(mentos->getTexture());
	case NORMAL_BULLET:
		return cocos2d::Sprite::createWithTexture(normalBullet->getTexture());
	case OVERLAY:
		return cocos2d::Sprite::createWithTexture(overlay->getTexture());
	case PLAYER:
		return cocos2d::Sprite::createWithTexture(player->getTexture());
	case PLAYER_BULLET:
		return cocos2d::Sprite::createWithTexture(playerBullet->getTexture());
	case SPAWN:
		return cocos2d::Sprite::createWithTexture(spawn->getTexture());
	case TEST_BULLET:
		return cocos2d::Sprite::createWithTexture(testBullet->getTexture());
	default:
		return nullptr;
	}
}
