#pragma once
#include "MainMenu.h"
#include "GameScene.h"
#include "Menu/MyMenu.h"
#include "Menu/MyMenuItem.h"

class GameOver : public MyMenu
{
public:
	static cocos2d::Scene* createScene(std::string);
	virtual bool init() override;
	void select();
	CREATE_FUNC(GameOver);	
private:
	MyMenuItem* gameOverText = nullptr;
};

