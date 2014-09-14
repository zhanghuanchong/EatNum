#include "WoodSwitch.h"

bool WoodSwitch::init(CCObject* target, SEL_CCControlHandler action, const char *onText, const char *offText)
{
	CCSprite *mask = CCSprite::create("switchMask.png");
	CCSprite *on = CCSprite::create("switchOn.png");
	CCSprite *off = CCSprite::create("switchOff.png");
	CCSprite *thumb = CCSprite::create("switchThumb.png");
	CCLabelTTF *onLabel = Util::createLabelTTF(onText, 30);
	onLabel->setColor(ccGREEN);
	CCLabelTTF *offLabel = Util::createLabelTTF(offText, 30);
	offLabel->setColor(ccRED);
	bool bRet = CCControlSwitch::initWithMaskSprite(mask, on, off, thumb, onLabel, offLabel);
	if (bRet)
	{
		this->addTargetWithActionForControlEvent(target, action, CCControlEventValueChanged);
	}
	return bRet;
}

WoodSwitch* WoodSwitch::create(CCObject* target, SEL_CCControlHandler action)
{
	WoodSwitch *pRet = new WoodSwitch();
    if (pRet && pRet->init(target, action, Util::text("On"), Util::text("Off")))
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

void WoodSwitch::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCControlSwitch::ccTouchEnded(pTouch, pEvent);
	if (this->isOn()) 
	{
		Util::playEffect("on.mp3");
	}
	else
	{
		Util::playEffect("off.mp3");
	}
}
