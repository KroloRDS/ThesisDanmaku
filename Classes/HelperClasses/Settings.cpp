#include "Settings.h"

const float Settings::DEFAULT_SCALE = 1.0f;
const int Settings::DEFAULT_HITBOXES = cocos2d::PhysicsWorld::DEBUGDRAW_NONE;;
float Settings::scale = DEFAULT_SCALE;
int Settings::resolution = DEFAULT_RESOLUTION;
int Settings::musicVolume = DEFAULT_MUSIC_VOLUME;
int Settings::effectVolume = DEFAULT_EFFECT_VOLUME;
int Settings::showHitboxes = DEFAULT_HITBOXES;

const float Settings::SIZES_X[3] = { 640.0f, 960.0f, 1280.0f };
const float Settings::SIZES_Y[3] = { 480.0f, 720.0f, 960.0f };

float Settings::getScale()
{
	return scale;
}

void Settings::setResolution(int newResolution)
{
	resolution = newResolution;
	scale = (float) SIZES_X[resolution] / SIZES_X[2];

	auto director = cocos2d::Director::getInstance();
	auto glview = director->getOpenGLView();
	glview->setFrameSize(SIZES_X[resolution], SIZES_Y[resolution]);
	glview->setDesignResolutionSize(SIZES_X[resolution], SIZES_Y[resolution], ResolutionPolicy::EXACT_FIT);
	director->setOpenGLView(glview);
}

int Settings::getResolution()
{
	return resolution;
}

void Settings::setMusicVolume(int newMusicVolume)
{
	musicVolume = newMusicVolume;
}

int Settings::getMusicVolume()
{
	return musicVolume;
}

void Settings::setEffectVolume(int newEffectVolume)
{
	effectVolume = newEffectVolume;
}

int Settings::getEffectVolume()
{
	return effectVolume;
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
