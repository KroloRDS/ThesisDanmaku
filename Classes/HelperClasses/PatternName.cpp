#include "PatternName.h"

PatternName* PatternName::createPatternName(std::string name)
{
	PatternName* ret = PatternName::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}

	ret->setScale(Settings::getScale());

	ret->label = cocos2d::Label::createWithTTF(name, ret->FONT_NAME, ret->FONT_SIZE);
	ret->label->setPosition(Settings::getTranslatedCoords(ret->INIT_POS));
	ret->label->enableOutline(cocos2d::Color4B::BLACK, 2);
	ret->label->setLocalZOrder(2);
	ret->addChild(ret->label);
	return ret;
}

void PatternName::update(float delta)
{
	if (timeInInitPos > 0.0f)
	{
		timeInInitPos -= delta;
		return;
	}

	if (absolutePos.y < DEST_POS.y)
	{
		absolutePos.y += delta * MOVE_SPEED;
		if (absolutePos.y > DEST_POS.y)
		{
			absolutePos.y = DEST_POS.y;
		}

		setPosition(Settings::getTranslatedCoords(absolutePos));
	}
}
