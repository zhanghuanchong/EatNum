#pragma once

#include "Util.h"

class SplashLayer :
	public CCLayerColor
{
private:
	CCSprite *m_pLogo;
	CCLabelTTF *m_pMotto;

public:
	CREATE_FUNC(SplashLayer)

	virtual bool init();
	virtual void onEnter();

	void onDidFinishEnter();
};
