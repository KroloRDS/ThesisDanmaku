#pragma once

#include "cocos2d.h"

class Settings
{
public:
	enum RESOLUTIONS { R640x480 = 0, R960x720, R1280x720, R1280x960, R1920x1080 };
	enum HITBOXES { NONE = 0, PLAYER_FOCUSED, PLAYER, PLAYER_AND_BULLETS };
	
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
	static void setHitboxOption(int);
	static int getPracticePattern();
	static void setPracticePattern(int);
	static void updateGLView();
	static cocos2d::Vec2 getTranslatedCoords(cocos2d::Vec2);
private:
	static float scale;
	static bool fullscreen;
	static int resolution;
	static int volume;
	static int showHitboxes;
	static int practicePattern;

	static const float DEFAULT_SCALE;
	static const int DEFAULT_RESOLUTION = RESOLUTIONS::R1280x960;
	static const int DEFAULT_VOLUME = 100;
	static const float SIZES_X[5];
	static const float SIZES_Y[5];
	static const int DEFAULT_HITBOXES = HITBOXES::PLAYER_FOCUSED;
	static const bool DEFAULT_FULLSCREEN = false;
};
