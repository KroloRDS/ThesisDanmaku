#include "MyMenuItem.h"

MyMenuItem::MyMenuItem(std::string text, std::string font, float fontSize)
{
	selectColor = cocos2d::Color3B(255, 255, 255);
	deselectColor = cocos2d::Color3B(153, 153, 153);
	selectOutlineColor = cocos2d::Color3B(153, 202, 224);
	deselectOutlineColor = cocos2d::Color3B(153, 202, 224);

	selected = false;
	doneAnimating = true;
	animationProgress = 0.0;
	animationTime = 0.2;
	outlineSize = fontSize / 15;

	label = cocos2d::Label::createWithTTF(text, font, fontSize);
	label->setColor(deselectColor);
	label->enableOutline(to4B(deselectOutlineColor), outlineSize);
	this->addChild(label);
}

void MyMenuItem::select()
{
	selected = true;
	doneAnimating = false;
}

void MyMenuItem::deselect()
{
	selected = false;
	doneAnimating = false;
}

bool MyMenuItem::isSelected()
{
	return selected;
}

void MyMenuItem::setSelectColor(cocos2d::Color3B color)
{
	selectColor = color;
}

void MyMenuItem::setDeselectColor(cocos2d::Color3B color)
{
	deselectColor = color;
}

void MyMenuItem::setSelectOutlineColor(cocos2d::Color3B color)
{
	selectOutlineColor = color;
}

void MyMenuItem::setDeselectOutlineColor(cocos2d::Color3B color)
{
	deselectOutlineColor = color;
}

void MyMenuItem::setAnimationTime(float time)
{
	animationTime = time;
}

std::string MyMenuItem::getName()
{
	return label->getString();
}

void MyMenuItem::update(float delta)
{
	if (doneAnimating)
	{
		return;
	}

	if (selected)
	{
		animationProgress += delta;
	}
	else
	{
		animationProgress -= delta;
	}

	if (animationProgress < 0.0)
	{
		animationProgress = 0.0;
		label->setColor(deselectColor);
		label->enableOutline(to4B(deselectOutlineColor), outlineSize);
		doneAnimating = true;
		return;
	}

	if (animationProgress > animationTime)
	{
		animationProgress = animationTime;
		label->setColor(selectColor);
		label->enableOutline(to4B(selectOutlineColor), outlineSize);
		doneAnimating = true;
		return;
	}

	float colorChangeProgress = animationProgress / animationTime;
	label->setColor(changeColor(colorChangeProgress, selectColor, deselectColor));
	label->enableOutline(to4B(changeColor(colorChangeProgress, selectOutlineColor, deselectOutlineColor)), outlineSize);
	return;
}

cocos2d::Color4B MyMenuItem::to4B(cocos2d::Color3B color)
{
	return cocos2d::Color4B(color.r, color.g, color.b, 255);
}

cocos2d::Color3B MyMenuItem::changeColor(float progress, cocos2d::Color3B color1, cocos2d::Color3B color2)
{
	int r = (color1.r - color2.r) * progress + color2.r;
	int g = (color1.g - color2.g) * progress + color2.g;
	int b = (color1.b - color2.b) * progress + color2.b;
	return cocos2d::Color3B(r, g, b);
}