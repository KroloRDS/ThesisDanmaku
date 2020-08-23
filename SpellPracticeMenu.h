#pragma once

#include "MyMenu.h"
#include "MainMenu.h"

class SpellPracticeMenu : public MyMenu
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(SpellPracticeMenu);
private:

};
