#include "SpellPracticeMenu.h"

enum options { SPELL_0 = 0, SPELL_1, SPELL_2, BACK };

cocos2d::Scene* SpellPracticeMenu::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = SpellPracticeMenu::create();
	scene->addChild(layer);
	return scene;
}

bool SpellPracticeMenu::init()
{
	if (!initMenu(cocos2d::Vec2(640, 680)))
	{
		return false;
	}

	std::vector<std::string> optionsStrings = { "Spell 1", "Spell 2", "Spell 3", "Back" };
	addMenuOptions(optionsStrings, 100.0, 160.0);
	menuOptions.at(selectedItem)->select();

	this->scheduleUpdate();
	return true;
}

void SpellPracticeMenu::select()
{
	Settings::setPracticePattern(selectedItem);
	selectedItem == BACK ?
		cocos2d::Director::getInstance()->replaceScene(MainMenu::createScene()) :
		cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
}
