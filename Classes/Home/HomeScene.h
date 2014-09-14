#pragma once
#include "Util.h"
#include "../Common/WoodScene.h"

class HomeScene :
	public WoodScene
{
private:
	CCArray *m_pLayers;
	bool m_bAnimationFinished;
	void easeIn(CCLayer *layer, float delay);

public:
	CREATE_FUNC(HomeScene);

	virtual bool init();

	virtual void onEnterTransitionDidFinish();

};

