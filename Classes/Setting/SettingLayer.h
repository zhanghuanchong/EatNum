#pragma once
#include "Util.h"
#include "../Common/WoodSwitch.h"

class SettingLayer :
	public CCLayer
{
private:
	WoodSwitch *m_pSwitchMusic;
	WoodSwitch *m_pSwitchEffect;

	void valueChanged(CCObject* sender, CCControlEvent controlEvent);

public:
	CREATE_FUNC(SettingLayer)

	virtual bool init();

};

