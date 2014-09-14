#include "HomeScene.h"
#include "HomeLogoLayer.h"
#include "HomeTitleLayer.h"
#include "HomeMenu.h"
#include "HomeSettingMenu.h"

bool HomeScene::init()
{
	bool bRet = WoodScene::init();
	if (bRet)
	{
		m_bAnimationFinished = false;

		Util::spriteFrameCache->addSpriteFramesWithFile("home.plist");

		m_pLayers = CCArray::create
		(
			HomeLogoLayer::create(), 
			HomeTitleLayer::create(),
			HomeMenu::create(),
			HomeSettingMenu::create(),
			NULL
		);
		m_pLayers->retain();
		
		CCSize size = Util::size;
		float heights[] = {
			0.85f, 0.65f, 0.38f, 0.1f
		};
		for (int i = 0, len = m_pLayers->count(); i < len; i++)
		{
			CCLayer *layer = (CCLayer *)m_pLayers->objectAtIndex(i);
			layer->setPosition(ccp(size.width * 1.5, size.height * heights[i]));
			this->addChild(layer);
		}
	}
	return bRet;
}

void HomeScene::onEnterTransitionDidFinish()
{
	WoodScene::onEnterTransitionDidFinish();

	if (!m_bAnimationFinished)
	{
		m_bAnimationFinished = true;
		for (int i = 0, len = m_pLayers->count(); i < len; i++)
		{
			this->easeIn((CCLayer *)m_pLayers->objectAtIndex(i), i * 0.1);
		}
	}
}

void HomeScene::easeIn( CCLayer *layer, float delay )
{
	CCSize size = Util::size;
	layer->setPositionX(size.width * 1.5);
	layer->runAction
	(
		CCSequence::create
		(
			CCDelayTime::create(delay),
			CCEaseExponentialOut::create
			(
				CCMoveBy::create(0.6f, ccp(-size.width, 0))
			),
			NULL
		)
	);
}