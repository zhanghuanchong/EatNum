#include "AboutScene.h"
#include "../Home/HomeScene.h"

bool AboutScene::init()
{
	if (!BaseScene::init())
    {
        return false;
	}

	auto bgLayer = LayerColor::create(Color4B(0, 136, 203, 255));
	this->addChild(bgLayer);

	auto m_pLogo = Sprite::create("logoMobile.png");
	m_pLogo->setScale(0.8f);
	m_pLogo->setPosition(U::cx, U::height * .8);
	this->addChild(m_pLogo);

	auto label = U::label("ABOUT_ME", 35, 1);
	label->setPosition(U::cx, U::cy);
	label->setHorizontalAlignment(TextHAlignment::LEFT);
	label->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(label);

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [](){
		Util::director->replaceScene(TransitionFlipX::create(0.3f, HomeScene::create()));
	});
	btnPlay->setPosition(U::cx, 120);
	this->addChild(btnPlay);

    return true;
}

void AboutScene::onEnterTransitionDidFinish()
{
	BaseScene::onEnterTransitionDidFinish();
}
