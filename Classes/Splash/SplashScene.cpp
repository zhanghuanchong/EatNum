#include "SplashScene.h"
#include "SplashLayer.h"

bool SplashScene::init()
{
	bool bRet = CCScene::init();
	if (bRet)
	{
		CCLayer *layer = SplashLayer::create();
		this->addChild(layer);
	}
	return bRet;
}
