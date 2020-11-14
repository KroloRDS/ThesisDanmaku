#pragma once

#include "SpellPracticeMenu.h"
#include "HelperClasses/MyMenu.h"

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

