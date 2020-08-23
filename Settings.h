#pragma once

#include "cocos2d.h"

class Settings
{
public:
	enum RESOLUTIONS { R640x480 = 0, R960x720, R1280x960 };
	
	static float getScale();
	static void setResolution(int);
	static int getResolution();
	static void setMusicVolume(int);
	static int getMusicVolume();
	static void setEffectVolume(int);
	static int getEffectVolume();
	static int getWindowSizeX();
	static int getWindowSizeY();
private:
	static float scale;
	static int resolution;
	static int musicVolume;
	static int effectVolume;

	static const float DEFAULT_SCALE;
	static const int DEFAULT_RESOLUTION = RESOLUTIONS::R1280x960;
	static const int DEFAULT_MUSIC_VOLUME = 100;
	static const int DEFAULT_EFFECT_VOLUME = 100;
	static const float SIZES_X[3];
	static const float SIZES_Y[3];
};
