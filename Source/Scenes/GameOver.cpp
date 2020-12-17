#include "GameOver.h"

enum options { RETRY = 0, MAIN_MENU, EXIT };

cocos2d::Scene* GameOver::createScene(std::string gameOverText, std::string score)
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);

	HighscoreLoader::save(Settings::getPracticePattern() + 1, std::stoi(score));

	layer->gameOverText->setText(gameOverText);
	layer->scoreCounter->setText(score);
	
	return scene;
}

bool GameOver::init()
{
	if (!initMenu(cocos2d::Vec2(640, 350)))
	{
		return false;
	}

	gameOverText = MyMenuItem::createMenuItem("", FONT_NAME, 100.0);
	gameOverText->setPos(cocos2d::Vec2(640, 800));
	gameOverText->select();
	addChild(gameOverText);

	scoreLabel = MyMenuItem::createMenuItem("Your score:", FONT_NAME, 60.0);
	scoreLabel->setPos(cocos2d::Vec2(640, 620));
	scoreLabel->select();
	addChild(scoreLabel);

	scoreCounter = MyMenuItem::createMenuItem("", FONT_NAME, 90.0);
	scoreCounter->setPos(cocos2d::Vec2(640, 510));
	scoreCounter->select();
	addChild(scoreCounter);

	std::vector<std::string> optionsStrings = { "Retry", "Main Menu", "Exit" };
	addMenuOptions(optionsStrings, 60.0, 100.0);
	menuOptions.at(selectedItem)->select();

	scheduleUpdate();
	return true;
}

void GameOver::select()
{
	switch (selectedItem)
	{
	case RETRY:
		cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	case MAIN_MENU:
		cocos2d::Director::getInstance()->replaceScene(MainMenu::createScene());
		break;
	case EXIT:
		cocos2d::Director::getInstance()->end();
		break;
	}
}
