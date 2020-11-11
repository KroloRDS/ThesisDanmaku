#include "AppDelegate.h"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = cocos2d::Director::getInstance();
	director->setAnimationInterval(1.0f / 90.0f);

	auto glview = cocos2d::GLViewImpl::create("ThesisDanmaku");
	glview->setFrameSize(Settings::getWindowSizeX(), Settings::getWindowSizeY());
	glview->setDesignResolutionSize(Settings::getWindowSizeX(), Settings::getWindowSizeY(), ResolutionPolicy::EXACT_FIT);
	director->setOpenGLView(glview);

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
