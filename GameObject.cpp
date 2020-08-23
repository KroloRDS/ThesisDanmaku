#include "GameObject.h"

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
	sprite = cocos2d::Sprite::create(str);
	sprite->setScale(Settings::getScale());
	addChild(sprite);
	setPos(pos);
}

void GameObject::update(float)
{
}

cocos2d::Sprite* GameObject::getSprite()
{
	return sprite;
}

void GameObject::setPos(cocos2d::Vec2 newPosition)
{
	absolutePos = newPosition;
	sprite->setPosition(newPosition * Settings::getScale());
}

cocos2d::Vec2 GameObject::getPos()
{
	return absolutePos;
}

bool GameObject::isSafeToDelete()
{
	return safeToDelete;
}
