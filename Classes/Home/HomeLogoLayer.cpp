#include "HomeLogoLayer.h"

bool HomeLogoLayer::init()
{
	bool bRet = CCLayer::init();
	if (bRet)
	{
		m_nRadius = 75;
		CCSize size = Util::size;

		CCSprite *spriteLogo = CCSprite::createWithSpriteFrameName("logoHome.png");
		this->addChild(spriteLogo);

		CCDrawNode *stencil = CCDrawNode::create();
		ccColor4F white = ccc4f(1, 1, 1, 1);
		int r = m_nRadius;
		CCPoint points[] = {
			ccp(-r, -r),
			ccp(r, -r),
			ccp(r, r),
			ccp(-r, r)
		};
		stencil->drawPolygon(points, 4, white, 0, white);

		CCClippingNode *clipper = CCClippingNode::create(stencil);
		this->addChild(clipper);
		clipper->setPosition(ccp(0, 67));

		m_pElectron = CCSprite::createWithSpriteFrameName("elec.png");
		clipper->addChild(m_pElectron);
		m_pElectron->setPosition(ccp(0, 0));
	}
	return bRet;
}

void HomeLogoLayer::onEnter()
{
	CCLayer::onEnter();

	float radius = m_nRadius * 1.5f;
	CCSequence *sequence = CCSequence::create
	(
		CCEaseCubicIn::create
		(
			CCMoveBy::create(0.5, ccp(radius, 0))
		),
		CCPlace::create(ccp(-radius, 0)),
		CCEaseCubicOut::create
		(
			CCMoveBy::create(0.5, ccp(radius, 0))
		),
		CCDelayTime::create(1),
		NULL
	);
	m_pElectron->runAction
	(
		CCRepeatForever::create(sequence)
	);
}