#pragma once
#include "Util.h"

class WoodLayer :
	public CCLayer
{
private:
	CCSprite *m_pBackground;
	
public:
	CREATE_FUNC(WoodLayer)

	virtual bool init();

};

