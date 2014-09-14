#include "WoodButton.h"

bool WoodButton::initWithTitle( const char *value, CCObject* target, SEL_MenuHandler selector )
{
	CCSprite *spriteNormal = CCSprite::createWithSpriteFrameName("btn.png");
	CCSprite *spriteActive = CCSprite::createWithSpriteFrameName("btnActive.png");
	CCSprite *spriteDisable = CCSprite::createWithSpriteFrameName("btn.png");
	bool bRet = CCMenuItemSprite::initWithNormalSprite(spriteNormal, spriteActive, spriteDisable, target, selector);
	if (bRet)
	{
		this->m_pLabel = Util::createLabelTTF(value, 45);
		this->addChild(m_pLabel);
		m_pLabel->setColor(ccBrown);
		m_pLabel->setPosition(ccp(spriteNormal->getContentSize().width * 0.5, 46));
	}
	return bRet;
}

void WoodButton::selected()
{
	CCMenuItemSprite::selected();
	m_pLabel->setPositionY(41);
	Util::playEffect("click.mp3");
}

void WoodButton::unselected()
{
	CCMenuItemSprite::unselected();
	m_pLabel->setPositionY(46);
}

WoodButton * WoodButton::create( const char *value, CCObject* target, SEL_MenuHandler selector )
{
	WoodButton *pRet = new WoodButton();
    if (pRet && pRet->initWithTitle(value, target, selector))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}
