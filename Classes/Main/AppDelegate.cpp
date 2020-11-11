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
	director->setOpenGLView(cocos2d::GLViewImpl::create("ThesisDanmaku"));
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
