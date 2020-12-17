#include "HighscoreScene.h"

cocos2d::Scene* HighscoreScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = HighscoreScene::create();
	scene->addChild(layer);
	return scene;
}

bool HighscoreScene::init()
{
	if (!initMenu(cocos2d::Vec2(640, 130)))
	{
		return false;
	}

	std::vector<std::string> optionsStrings = { "Back" };
	addMenuOptions(optionsStrings, 80.0, 160.0);
	menuOptions.at(selectedItem)->select();

	modeLabel = MyMenuItem::createMenuItem("", FONT_NAME, 100.0);
	modeLabel->setPos(cocos2d::Vec2(640, 870));
	modeLabel->select();
	addChild(modeLabel);

	for (int i = 0; i < SCORE_ENTRIES; i++)
	{
		scoreLabels[i] = MyMenuItem::createMenuItem("", FONT_NAME, 40.0);
		scoreLabels[i]->setPos(cocos2d::Vec2(640, 700 - (i * 50)));
		scoreLabels[i]->select();
		addChild(scoreLabels[i]);
	}

	scores = HighscoreLoader::load();
	updateScores();

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(HighscoreScene::pressKey, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	this->scheduleUpdate();
	return true;
}

void HighscoreScene::pressKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SELECT_SFX);
		mode = meunuWarpAround(mode, -1, SCORE_MODES - 1);
		updateScores();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SELECT_SFX);
		mode = meunuWarpAround(mode, 1, SCORE_MODES - 1);
		updateScores();
		break;
	}
}

void HighscoreScene::updateScores()
{
	modeLabel->setText(modeStrings.at(mode));
	for (int i = 0; i < SCORE_ENTRIES; i++)
	{
		std::string text = std::to_string(i + 1) + ". ";
		if (scores.at(SCORE_ENTRIES * mode + i) != nullptr)
		{
			text += scores.at(SCORE_ENTRIES * mode + i)->toString();
		}
		scoreLabels[i]->setText(text);
	}
}

void HighscoreScene::select()
{
	cocos2d::Director::getInstance()->replaceScene(MainMenu::createScene());
}
