#pragma once
#include "Util.h"

class WoodButton :
	public CCMenuItemSprite
{
private:
	CCLabelTTF *m_pLabel;

public:
	static WoodButton *create(const char *value, CCObject* target, SEL_MenuHandler selector);

	virtual bool initWithTitle(const char *value, CCObject* target, SEL_MenuHandler selector);

	virtual void selected();

	virtual void unselected();

};

