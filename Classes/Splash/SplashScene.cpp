#include "SplashScene.h"
#include "../Home/HomeScene.h"

bool SplashScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
	auto bgLayer = LayerColor::create(Color4B(0, 136, 203, 255));
	this->addChild(bgLayer);

	m_pLogo = Sprite::create("image/logoMobile.png");
	m_pLogo->setScale(0.1f);
	m_pLogo->setPosition(U::cx, U::height * .6);
	this->addChild(m_pLogo);
    
	m_pMotto = Util::label("Mobile Education Game Expert", 45, 1);
	m_pMotto->setPosition(U::cx, - m_pMotto->getContentSize().height);
	this->addChild(m_pMotto);

    return true;
}

void SplashScene::onEnterTransitionDidFinish()
{
	ScaleTo *scaleAction = ScaleTo::create(0.5f, 0.8f);
	m_pLogo->runAction(EaseBounceOut::create(scaleAction));

	MoveTo *moveAction = MoveTo::create(0.3f, Vec2(U::cx, U::height * 0.1));
	auto callback = [&](){
		Util::playBackgroundMusic();
		Util::director->replaceScene(CCTransitionFade::create(1, HomeScene::create()));
	};
	Sequence *sequence = Sequence::create(
		DelayTime::create(0.5),
		EaseBounceOut::create(moveAction),
		DelayTime::create(1),
		CallFunc::create(callback),
		NULL
	);
	m_pMotto->runAction(sequence);
}
