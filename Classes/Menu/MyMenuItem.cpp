#include "MyMenuItem.h"

MyMenuItem* MyMenuItem::createMenuItem(std::string text, std::string font, float fontSize)
{
	MyMenuItem* ret = MyMenuItem::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}
	
	ret->setScale(Settings::getScale());

	ret->outlineSize = (int)std::round(fontSize / OUTLINE_SIZE_SCALE);

	ret->label = cocos2d::Label::createWithTTF(text, font, fontSize);
	ret->label->setColor(ret->deselectColor);
	ret->label->enableOutline(ret->to4B(ret->deselectOutlineColor), ret->outlineSize);
	ret->addChild(ret->label);
	return ret;
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

void MyMenuItem::setText(std::string string)
{
	label->setString(string);
}

void MyMenuItem::setPos(cocos2d::Vec2 pos)
{
	absolutePos = pos;
	this->setPosition(pos * Settings::getScale());
}

cocos2d::Vec2 MyMenuItem::getPos()
{
	return absolutePos;
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

	if (animationProgress < 0.0f)
	{
		animationProgress = 0.0f;
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
	int r = (int)std::round((color1.r - color2.r) * progress + color2.r);
	int g = (int)std::round((color1.g - color2.g) * progress + color2.g);
	int b = (int)std::round((color1.b - color2.b) * progress + color2.b);
	return cocos2d::Color3B(r, g, b);
}
