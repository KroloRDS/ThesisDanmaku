#pragma once

#include "cocos2d.h"
#include "GameOver.h"
#include "PauseScene.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "cocos\editor-support\cocostudio\SimpleAudioEngine.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(GameScene);
	void update(float) override;

	static const cocos2d::Vec2 GAME_INNER_BOUNDS[4];
	static const cocos2d::Vec2 GAME_OUTER_BOUNDS[4];

private:
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	
	MyMenuItem* scoreLabel = nullptr;
	MyMenuItem* scoreCounter = nullptr;
	unsigned long int displayScore = 0;
	unsigned long int score = 0;

	MyMenuItem* patternGrazeLabel = nullptr;
	MyMenuItem* patternGrazeCounter = nullptr;
	int patternGraze = 0;

	MyMenuItem* totalGrazeLabel = nullptr;
	MyMenuItem* totalGrazeCounter = nullptr;
	int totalGraze = 0;

	MyMenuItem* livesLabel = nullptr;
	
	MyMenuItem* fpsCounter = nullptr;
	float fpsUpdate = 0.0f;

	MyMenuItem* spellBonusLabel = nullptr;
	float spellBonusLabelUpdate = 0.0f;

	bool noHitBonus = true;
	bool showBonus = false;
	bool noHitBonusSFXPlayed = false;

	void addListeners();
	void addUIElements();
	void addOverlay();
	
	bool onContactBegin(cocos2d::PhysicsContact&);
	void pressKey(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void releaseKey(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

	void onContact(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*);

	void hitEnemy();
	void damageEnemy(cocos2d::Vec2);
	void nextPattern();
	void updateSpellBonusLabel(float);
	void updateFpsCounter(float);
	void updateScoreCounter();

	cocos2d::RenderTexture* takeScreenshot();
	bool pause = false;

	const int INIT_HIT_POINT_VALUE = 1000;
	const float UI_TEXT_X_POS = 1030.0f;
	const float UI_TEXT_Y_POS = 850.0f;
	const float UI_TEXT_Y_MARGIN = 60.0f;
	const float UI_FONT_SIZE = 50.0f;
	const std::string UI_FONT_NAME = "arial.ttf";

	const float FPS_COUNTER_UPDATE = 0.4f;
	const float FPS_COUNTER_FONT_SIZE = 15.0f;

	const float SPELL_BONUS_LABEL_DELAY_TIME = 2.0f;
	const float SPELL_BONUS_LABEL_VISIBLE_TIME = 2.0f;
	const float SPELL_BONUS_LABEL_FADE_TIME = 2.0f;
	const float SPELL_BONUS_LABEL_FONT_SIZE = 90.0f;

	const cocos2d::Vec2 FPS_COUNTER_POS = cocos2d::Vec2(780.0f, 50.0f);
	const cocos2d::Vec2 SPELL_BONUS_LABEL_POS = cocos2d::Vec2(440.0f, 700.0f);
};
