#pragma once

#include "MainMenu.h"
#include "HelperClasses/Score.h"
#include "HelperClasses/MyMenu.h"
#include "HelperClasses/HighscoreLoader.h"

class HighscoreScene : public MyMenu
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(HighscoreScene);
private:
	const static int SCORE_MODES = HighscoreLoader::SCORE_MODES;
	const static int SCORE_ENTRIES = HighscoreLoader::SCORE_ENTRIES;
	const std::vector<std::string> modeStrings = { "All Spells", "Spell 1", "Spell 2", "Spell 3" };

	int mode = 0;
	MyMenuItem* modeLabel = nullptr;

	std::vector<Score*>scores = {};
	MyMenuItem* scoreLabels[SCORE_ENTRIES] = { nullptr };

	void pressKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*);
	void updateScores();
};

