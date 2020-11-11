#include "Settings.h"

const float Settings::DEFAULT_SCALE = 1.0f;
const int Settings::DEFAULT_HITBOXES = cocos2d::PhysicsWorld::DEBUGDRAW_NONE;
float Settings::scale = DEFAULT_SCALE;
bool Settings::fullscreen = DEFAULT_FULLSCREEN;
int Settings::resolution = DEFAULT_RESOLUTION;
int Settings::volume = DEFAULT_VOLUME;
int Settings::showHitboxes = DEFAULT_HITBOXES;
int Settings::practicePattern = 0;

const float Settings::SIZES_X[4] = { 640.0f, 960.0f, 1280.0f, 1440.0f };
const float Settings::SIZES_Y[4] = { 480.0f, 720.0f, 960.0f, 1080.0f };

void Settings::updateGLView()
{
	cocos2d::GLViewImpl* glview = 
		(cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();

	glview->setFrameSize(SIZES_X[resolution], SIZES_Y[resolution]);
	glview->setDesignResolutionSize(SIZES_X[resolution], SIZES_Y[resolution], ResolutionPolicy::SHOW_ALL);
	fullscreen ? glview->setFullscreen() : glview->setWindowed(SIZES_X[resolution], SIZES_Y[resolution]);
	cocos2d::Director::getInstance()->setOpenGLView(glview);
}

float Settings::getScale()
{
	return scale;
}

void Settings::setResolution(int newResolution)
{
	resolution = newResolution;
	scale = (float) SIZES_Y[resolution] / SIZES_Y[2];

	updateGLView();
}

int Settings::getResolution()
{
	return resolution;
}

void Settings::setVolume(int newVolume)
{
	volume = newVolume;
}

int Settings::getVolume()
{
	return volume;
}

void Settings::setPracticePattern(int newPracticePattern)
{
	practicePattern = newPracticePattern;
}

int Settings::getPracticePattern()
{
	return practicePattern;
}

void Settings::setFullscreen(bool newFullscreen)
{
	fullscreen = newFullscreen;
	setResolution(1);
}

bool Settings::isFullscren()
{
	return fullscreen;
}

float Settings::getWindowSizeX()
{
	return SIZES_X[resolution];
}

float Settings::getWindowSizeY()
{
	return SIZES_Y[resolution];
}

int Settings::getHitboxOption()
{
	return showHitboxes;
}

void Settings::setHitboxOption(bool newOption)
{
	if (newOption)
	{
		showHitboxes = cocos2d::PhysicsWorld::DEBUGDRAW_ALL;
	}
	else
	{
		showHitboxes = cocos2d::PhysicsWorld::DEBUGDRAW_NONE;
	}
}
