#pragma once
#include "Util.h"

class WoodLayer;

class WoodScene :
	public CCScene
{
private:
	WoodLayer *m_pBackground;
	CCMenu *m_pMenuBack;
	CCMenuItemSprite *m_pMenuItemBack;

public:
	CREATE_FUNC(WoodScene)

	virtual bool init();
	virtual void showBackButton(bool bAnimation);
	virtual void onBack(CCObject *sender);
};

