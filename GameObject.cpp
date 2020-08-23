#include "GameObject.h"

GameObject::GameObject(std::string str, cocos2d::Vec2 pos)
{
	sprite = cocos2d::Sprite::create(str);
	sprite->setScale(Settings::getScale());
	this->addChild(sprite);
	setPos(pos);
}

cocos2d::Sprite* GameObject::getSprite()
{
	return sprite;
}

void GameObject::setPos(cocos2d::Vec2 pos)
{
	absolutePos = pos;
	sprite->setPosition(pos * Settings::getScale());
}

cocos2d::Vec2 GameObject::getPos()
{
	return absolutePos;
}
