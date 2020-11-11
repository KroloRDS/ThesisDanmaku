#pragma once

#include "cocos2d.h"

class Settings
{
public:
	enum RESOLUTIONS { R640x480 = 0, R960x720, R1280x960, R1440x1080 };
	
	static float getScale();
	static void setResolution(int);
	static int getResolution();
	static void setVolume(int);
	static int getVolume();
	static void setFullscreen(bool);
	static bool isFullscren();
	static float getWindowSizeX();
	static float getWindowSizeY();
	static int getHitboxOption();
	static void setHitboxOption(bool);
	static void updateGLView();
private:
	static float scale;
	static int resolution;
	static int volume;
	static bool fullscreen;
	static int showHitboxes;

	static const float DEFAULT_SCALE;
	static const int DEFAULT_RESOLUTION = RESOLUTIONS::R1280x960;
	static const int DEFAULT_VOLUME = 100;
	static const float SIZES_X[4];
	static const float SIZES_Y[4];
	static const int DEFAULT_HITBOXES;
	static const bool DEFAULT_FULLSCREEN = false;
};
