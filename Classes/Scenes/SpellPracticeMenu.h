#pragma once

#include "MainMenu.h"
#include "Menu/MyMenu.h"

class SpellPracticeMenu : public MyMenu
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(SpellPracticeMenu);
private:

};
