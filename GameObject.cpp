#include "GameObject.h"

GameObject::GameObject(std::string str)
{
	sprite.create(str);
}

cocos2d::Sprite* GameObject::getSprite()
{
	return &sprite;
}
