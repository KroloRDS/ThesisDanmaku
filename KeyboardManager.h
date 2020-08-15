#pragma once

#include "cocos2d.h"

class KeyboardManager
{
public:
	bool isPressed(cocos2d::EventKeyboard::KeyCode);
	void pressKey(cocos2d::EventKeyboard::KeyCode);
	void releaseKey(cocos2d::EventKeyboard::KeyCode);
	float getPressTime(cocos2d::EventKeyboard::KeyCode);
private:
	std::unordered_map<
		cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point
	> keyPressedTime;
};