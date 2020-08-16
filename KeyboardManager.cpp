#include "KeyboardManager.h"

std::unordered_map<
	cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point
> KeyboardManager::keyPressedTime = {};

bool KeyboardManager::isPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyPressedTime.find(keyCode) != keyPressedTime.end())
	{
		return true;
	}
	return false;
}

void KeyboardManager::pressKey(cocos2d::EventKeyboard::KeyCode keyCode)
{
	keyPressedTime[keyCode] = std::chrono::high_resolution_clock::now();
}

void KeyboardManager::releaseKey(cocos2d::EventKeyboard::KeyCode keyCode)
{
	keyPressedTime.erase(keyCode);
}

float KeyboardManager::getPressTime(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyPressedTime.find(keyCode) != keyPressedTime.end())
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::high_resolution_clock::now() - keyPressedTime[keyCode]).count() / 1000.0;
	}
	return 0.0;
}