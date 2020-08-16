#pragma once

#include "cocos2d.h"

class KeyboardManager
{
public:
	static bool isPressed(cocos2d::EventKeyboard::KeyCode);
	static void pressKey(cocos2d::EventKeyboard::KeyCode);
	static void releaseKey(cocos2d::EventKeyboard::KeyCode);
	static float getPressTime(cocos2d::EventKeyboard::KeyCode);
private:
	static std::unordered_map<
		cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point
	> keyPressedTime;
};