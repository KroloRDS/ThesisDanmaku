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
	director->runWithScene(MainMenu::createScene());
	Settings::updateGLView();
	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
}

void AppDelegate::applicationWillEnterForeground()
{
}
