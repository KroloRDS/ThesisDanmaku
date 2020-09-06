#pragma once

#include "cocos2d.h"
#include "Scenes/MainMenu.h"
#include "HelperClasses/Settings.h"

class  AppDelegate : private cocos2d::Application
{
public:
	AppDelegate();
	virtual ~AppDelegate();

	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
};
