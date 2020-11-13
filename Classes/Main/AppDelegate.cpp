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
	director->setOpenGLView(cocos2d::GLViewImpl::create("ThesisDanmaku"));
	director->setDisplayStats(true);
	Settings::updateGLView();

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
