#include "SettingAboutLayer.h"

bool SettingAboutLayer::init()
{
	bool bRet = CCLayer::init();
	if (bRet)
	{
		CCSize size = Util::size;

		CCSprite *pLogo = CCSprite::create("logoWood.png");
		pLogo->setPosition(ccp(0, size.height * .5));
		this->addChild(pLogo);

		CCLabelTTF *pLabel = Util::createLabelTTF("Programmer: Hans Zhang");
		pLabel->setPosition(ccp(0, 260));
		pLabel->setColor(ccBrown);
		this->addChild(pLabel);

		pLabel = Util::createLabelTTF("Designer: Ruth Wu");
		pLabel->setPosition(ccp(0, 180));
		pLabel->setColor(ccBrown);
		this->addChild(pLabel);

		pLabel = Util::createLabelTTF("Composer: Frank Meacham");
		pLabel->setPosition(ccp(0, 100));
		pLabel->setColor(ccBrown);
		this->addChild(pLabel);
	}
	return bRet;
}
