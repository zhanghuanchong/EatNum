#include "WoodLayer.h"

bool WoodLayer::init()
{
	bool bRet = CCLayer::init();
	if (bRet)
	{
		m_pBackground = CCSprite::create("bgWood.jpg");
		this->addChild(m_pBackground, -1);
		m_pBackground->setPosition(ccp(Util::size.width / 2, Util::size.height / 2));
	}
	return bRet;
}
