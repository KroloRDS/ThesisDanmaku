#pragma once

#include "cocos2d.h"
#include "HelperClasses/Settings.h"

class PatternName : public cocos2d::Node
{
public:
	static PatternName* createPatternName(std::string);
	CREATE_FUNC(PatternName);
	void update(float);
private:
	float timeInInitPos = 1.0f;
	cocos2d::Vec2 absolutePos = cocos2d::Vec2(0, 0);

	cocos2d::Label* label = nullptr;

	const float MOVE_SPEED = 500.0f;
	const float FONT_SIZE = 20.0f;
	const std::string FONT_NAME = "fonts/arial.ttf";
	const cocos2d::Vec2 INIT_POS = cocos2d::Vec2(600, 100);
	const cocos2d::Vec2 DEST_POS = cocos2d::Vec2(600, 750);
};

