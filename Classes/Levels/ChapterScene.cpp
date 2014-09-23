#include "ChapterScene.h"
#include "Home/HomeScene.h"
#include "Common/ScalableSprite.h"

bool ChapterScene::init()
{
    if ( !Scene::init() )
    {
        return false;
	}

	auto bgLayer = LayerColor::create(Color4B(230, 142, 79, 255));
	this->addChild(bgLayer);

	auto label = U::label("Select Chapter", 50, 1);
	label->setPosition(U::cx, U::height * .85);
	this->addChild(label);

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [](){
		Util::director->replaceScene(TransitionSlideInL::create(0.2f, HomeScene::create()));
	});
	btnPlay->setPosition(U::cx, 120);
	this->addChild(btnPlay);

    return true;
}

void ChapterScene::onEnterTransitionDidFinish()
{

}
