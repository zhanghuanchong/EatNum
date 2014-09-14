#include "SplashLayer.h"
#include "../Home/HomeScene.h"

bool SplashLayer::init()
{
	bool bRet = CCLayerColor::initWithColor(ccc4(0, 136, 203, 255));
	if (bRet)
	{
		m_pLogo = CCSprite::create("logoMobile.png");
		CCSize size = Util::size;
		float scale = size.width / m_pLogo->getContentSize().width;
		m_pLogo->setScale(scale / 5);
		m_pLogo->setPosition(ccp(size.width / 2, size.height * .6));
		this->addChild(m_pLogo);

		m_pMotto = Util::createLabelTTF("Mobile Education Game Expert", 40);
		scale = size.width / m_pMotto->getContentSize().width;
		m_pMotto->setPosition(ccp(size.width / 2, -m_pMotto->getContentSize().height * scale / 2));
		this->addChild(m_pMotto);
	}
	return bRet;
}


void SplashLayer::onEnter()
{
	CCLayerColor::onEnter();

	CCScaleTo *scaleAction = CCScaleTo::create(1, 1);
	m_pLogo->runAction(CCEaseBounceOut::create(scaleAction));
	
	CCSize size = Util::size;
	CCEaseBounceOut *moveAction = CCEaseBounceOut::create
	(
		CCMoveTo::create(0.3f, ccp(size.width / 2, size.height * 0.15))
	);
	m_pMotto->runAction
	(
		CCSequence::create
		(
			CCDelayTime::create(0.5),
			moveAction,
			CCDelayTime::create(1),
			CCCallFunc::create(this, callfunc_selector(SplashLayer::onDidFinishEnter)),
			NULL
		)
	);
}

void SplashLayer::onDidFinishEnter()
{
	Util::spriteFrameCache->addSpriteFramesWithFile("common.plist");

	Util::audioEngine->preloadBackgroundMusic(kConfigMusic);
	const char *effects[] = {
		"on.mp3",
		"off.mp3",
		"click.mp3"
	};
	for (int i = 0; i < 3; i++)
	{
		Util::audioEngine->preloadEffect(effects[i]);
	}

	if (Util::userDefault->getBoolForKey(kConfigMusic, true))
	{
		Util::audioEngine->playBackgroundMusic(kFileBgMusic);
	}

	Util::init();

	Util::director->replaceScene(CCTransitionFade::create(0.5, HomeScene::create()));
}