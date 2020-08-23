#pragma once

#include "cocos2d.h"
#include "Settings.h"

class MyMenuItem : public cocos2d::Node
{
public:
	static MyMenuItem* createMenuItem(std::string, std::string, float);
	CREATE_FUNC(MyMenuItem);
	void update(float delta);
	void select();
	void deselect();
	bool isSelected();
	void setSelectColor(cocos2d::Color3B);
	void setDeselectColor(cocos2d::Color3B);
	void setSelectOutlineColor(cocos2d::Color3B);
	void setDeselectOutlineColor(cocos2d::Color3B);
	void setAnimationTime(float);
	void setText(std::string);
	void setPos(cocos2d::Vec2);
	cocos2d::Vec2 getPos();
private:
	bool selected = false;
	bool doneAnimating = true;
	float animationProgress = 0.0;
	float animationTime = 0.2;
	
	int outlineSize = 0;
	cocos2d::Vec2 absolutePos = cocos2d::Vec2(0, 0);
	
	cocos2d::Label* label = nullptr;
	cocos2d::Color3B selectColor = cocos2d::Color3B(255, 255, 255);
	cocos2d::Color3B deselectColor = cocos2d::Color3B(153, 153, 153);
	cocos2d::Color3B selectOutlineColor = cocos2d::Color3B(153, 202, 224);
	cocos2d::Color3B deselectOutlineColor = cocos2d::Color3B(153, 202, 224);
	
	cocos2d::Color4B to4B(cocos2d::Color3B);
	cocos2d::Color3B changeColor(float, cocos2d::Color3B, cocos2d::Color3B);
};
