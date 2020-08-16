#pragma once

#include "MyMenu.h"

class OptionsMenu : public MyMenu
{
public:
	void update(float) override;
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(OptionsMenu);
private:
	int selectedResolution;
	int musicVolume;
	int soundVolume;
	const int maxVolume = 100;
	
	std::vector<std::string> resolutionOptionStrings;
	cocos2d::Vector<MyMenuItem*> menuLeftColumn;
};