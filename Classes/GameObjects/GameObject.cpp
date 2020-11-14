#include "GameObject.h"
#include "Scenes/GameScene.h"
#include "PlayerBullet.h"

GameObject* GameObject::createGameObject(std::string str, cocos2d::Vec2 pos)
{
	GameObject* ret = GameObject::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->initGameObj(str, pos);
	return ret;
}

void GameObject::initGameObj(std::string str, cocos2d::Vec2 pos)
{
	if (!str.empty())
	{
		sprite = cocos2d::Sprite::create(str);
		sprite->setScale(Settings::getScale());
		addChild(sprite);
	}
	setPos(pos);
}

cocos2d::Sprite* GameObject::getSprite()
{
	return sprite;
}

void GameObject::setPos(cocos2d::Vec2 newPosition)
{
	absolutePos = newPosition;
	if (sprite != nullptr)
	{
		sprite->setPosition(Settings::getTranslatedCoords(newPosition));
	}
}

cocos2d::Vec2 GameObject::getPos()
{
	return absolutePos;
}

cocos2d::Rect GameObject::getSpriteBoundingBox()
{
	return sprite->getBoundingBox();
}

bool GameObject::isOutOfBounds()
{
	return (absolutePos.x < GameScene::GAME_OUTER_BOUNDS[0].x ||
		absolutePos.y < GameScene::GAME_OUTER_BOUNDS[0].y ||
		absolutePos.x > GameScene::GAME_OUTER_BOUNDS[2].x ||
		absolutePos.y > GameScene::GAME_OUTER_BOUNDS[2].y);
}

bool GameObject::isOutOfInnerBounds()
{
	return (absolutePos.x < GameScene::GAME_INNER_BOUNDS[0].x ||
		absolutePos.y < GameScene::GAME_INNER_BOUNDS[0].y ||
		absolutePos.x > GameScene::GAME_INNER_BOUNDS[2].x ||
		absolutePos.y > GameScene::GAME_INNER_BOUNDS[2].y);
}
