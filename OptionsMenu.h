#pragma once

#include "MyMenu.h"

class OptionsMenu : public MyMenu
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(OptionsMenu);
private:

};