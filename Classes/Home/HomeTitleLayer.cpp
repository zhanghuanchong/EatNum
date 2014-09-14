#include "HomeTitleLayer.h"

bool HomeTitleLayer::init()
{
	bool bRet = CCLayer::init();
	if (bRet)
	{
		CCSprite *title = CCSprite::createWithSpriteFrameName("title.png");
		this->addChild(title);
	}
	return bRet;
}
