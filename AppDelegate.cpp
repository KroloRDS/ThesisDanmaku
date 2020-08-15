#include "AppDelegate.h"
#include "MainMenu.h"

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
		glview->setFrameSize(1280, 960);
		glview->setDesignResolutionSize(1280, 960, ResolutionPolicy::EXACT_FIT);
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