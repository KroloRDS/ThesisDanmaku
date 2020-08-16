#include "AppDelegate.h"
#include "MainMenu.h"
#include "Settings.h"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = cocos2d::Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview)
	{
		glview = cocos2d::GLViewImpl::create("ThesisDanmaku alpha 1.0");
		glview->setFrameSize(Settings::getWindowSizeX(), Settings::getWindowSizeY());
		glview->setDesignResolutionSize(Settings::getWindowSizeX(), Settings::getWindowSizeY(), ResolutionPolicy::EXACT_FIT);
		director->setOpenGLView(glview);
	}

	auto scene = MainMenu::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
}

void AppDelegate::applicationWillEnterForeground()
{
}