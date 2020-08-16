#include "Settings.h"

const float Settings::DEFAULT_SCALE = 1.0;
float Settings::scale = DEFAULT_SCALE;
int Settings::resolution = DEFAULT_RESOLUTION;
int Settings::musicVolume = DEFAULT_MUSIC_VOLUME;
int Settings::effectVolume = DEFAULT_EFFECT_VOLUME;

const int Settings::SIZES_X[3] = {640,960,1280};
const int Settings::SIZES_Y[3] = {480,720,960};

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

int Settings::getWindowSizeX()
{
	return SIZES_X[resolution];
}

int Settings::getWindowSizeY()
{
	return SIZES_Y[resolution];
}
