#pragma once

#include "GameScene.h"
#include "SettingsMenu.h"
#include "SpellPracticeMenu.h"
#include "HelperClasses/MyMenu.h"

class MainMenu : public MyMenu
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(MainMenu);
};
