#pragma once
#include "Menu/MyMenu.h"
#include "SpellPracticeMenu.h"

class PauseScene : public MyMenu
{
public:
	static cocos2d::Scene* createScene(cocos2d::RenderTexture*);
	virtual bool init() override;
	void select();
	CREATE_FUNC(PauseScene);
private:
	static cocos2d::DrawNode* dimEffect();
};

