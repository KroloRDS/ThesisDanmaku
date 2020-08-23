#include "KeyboardManager.h"

std::unordered_map<
	cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point
> KeyboardManager::keyPressedTime = {};

const std::vector<cocos2d::EventKeyboard::KeyCode> KeyboardManager::arrowKeys =
{
	cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW,
	cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW,
	cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW,
	cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW
};

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

std::vector<cocos2d::EventKeyboard::KeyCode> KeyboardManager::getPressedArrows()
{
	std::vector<cocos2d::EventKeyboard::KeyCode> pressed = {};
	for (cocos2d::EventKeyboard::KeyCode key : arrowKeys)
	{
		if (KeyboardManager::isPressed(key))
		{
			pressed.push_back(key);
		}
	}
	return pressed;
}
