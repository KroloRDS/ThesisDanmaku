#pragma once

#include "MainMenu.h"
#include "GameScene.h"
#include "HelperClasses/MyMenu.h"
#include "HelperClasses/MyMenuItem.h"
#include "HelperClasses/HighscoreLoader.h"

class GameOver : public MyMenu
{
public:
	static cocos2d::Scene* createScene(std::string, std::string);
	virtual bool init() override;
	void select();
	CREATE_FUNC(GameOver);	
private:
	MyMenuItem* gameOverText = nullptr;
	MyMenuItem* scoreCounter = nullptr;
	MyMenuItem* scoreLabel = nullptr;
};

