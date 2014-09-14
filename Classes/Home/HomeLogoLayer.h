#pragma once
#include "Util.h"

class HomeLogoLayer :
	public CCLayer
{
private:
	int m_nRadius;
	CCSprite *m_pElectron;

public:
	CREATE_FUNC(HomeLogoLayer)

	virtual bool init();

	virtual void onEnter();

};

