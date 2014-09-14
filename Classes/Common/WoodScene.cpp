#include "WoodScene.h"
#include "WoodLayer.h"

bool WoodScene::init()
{
	bool bRet = CCScene::init();
	if (bRet)
	{
		m_pBackground = WoodLayer::create();
		this->addChild(m_pBackground, -1);

		m_pMenuItemBack = CCMenuItemSprite::create
		(
			CCSprite::createWithSpriteFrameName("back.png"),
			CCSprite::createWithSpriteFrameName("backActive.png"),
			this,
			menu_selector(WoodScene::onBack)
		);
		CCSize size = Util::size;
		m_pMenuItemBack->setPosition(-size.width * 0.5 + 70, size.height * 0.5 - 70);

		m_pMenuBack = CCMenu::createWithItem(m_pMenuItemBack);
		m_pMenuBack->retain();
	}
	return bRet;
}

void WoodScene::showBackButton( bool bAnimation )
{
	this->addChild(m_pMenuBack);
	if (bAnimation)
	{
		m_pMenuItemBack->setScale(0.1f, 0.1f);
		m_pMenuItemBack->runAction
		(
			CCEaseBackOut::create
			(
				CCScaleTo::create(0.3f, 1, 1)
			)
		);
	}
}

void WoodScene::onBack(CCObject *sender)
{
	Util::popWoodScene();
}
