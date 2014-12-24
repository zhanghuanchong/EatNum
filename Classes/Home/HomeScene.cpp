#include "HomeScene.h"
#include "../Levels/ChapterScene.h"
#include "../Common/ScalableSprite.h"
#include "../Game/GameScene.h"

bool HomeScene::init()
{
    if ( !BaseScene::init() )
    {
        return false;
    }
    
	auto bgLayer = LayerColor::create(Color4B(195, 75, 134, 255));
	this->addChild(bgLayer);

	labelNom = U::label("NOM", 150, 1);
	labelNom->setPosition(U::cx - 20, U::cy + 70 + 70);
	this->addChild(labelNom);

	labelNum = U::label("NUM", 150, 1);
	labelNum->setPosition(U::cx + 20, U::cy + 70 - 70);
	this->addChild(labelNum);

	bool tutorial = U::userDefault->getBoolForKey("tutorial", true);

	ScalableSprite *btnPlay = ScalableSprite::create("play.png", [tutorial](){
		if (tutorial)
		{
			U::userDefault->setBoolForKey("tutorial", false);
			Util::director->replaceScene(TransitionSlideInR::create(0.2f, GameScene::createWithLevel(0, 0)));
		}
		else
		{
			int currentChapter = U::userDefault->getIntegerForKey("currentChapter");
			int currentLevel = U::userDefault->getIntegerForKey("currentLevel");
			Util::director->replaceScene(TransitionSlideInR::create(0.2f, GameScene::createWithLevel(currentLevel, currentChapter)));
		}
	});

	if (tutorial)
	{
		btnPlay->setPosition(U::cx, U::height / 4);
	}
	else
	{
		btnPlay->setPosition(U::cx, U::height / 4 + 70);

		ScalableSprite *btnMenu = ScalableSprite::create("menu_green.png", [](){
			Util::director->replaceScene(TransitionSlideInR::create(0.2f, ChapterScene::create()));
		});
		btnMenu->setPosition(U::cx, U::height / 4 - 70);
		this->addChild(btnMenu);
	}
	this->addChild(btnPlay);
    
    return true;
}

void HomeScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();

	MoveTo *actionDown = MoveTo::create(0.5, Vec2(U::cx - 20, U::cy + 80 + 40));
	MoveTo *actionUp = MoveTo::create(0.5, Vec2(U::cx - 20, U::cy + 80 + 70));
	Sequence *seq = Sequence::createWithTwoActions(
		EaseSineIn::create(actionDown),
		EaseSineOut::create(actionUp)
	);
	RepeatForever *repeat = RepeatForever::create(seq);
	labelNom->runAction(repeat);

	actionUp = MoveTo::create(0.5, Vec2(U::cx + 20, U::cy + 80 - 40));
	actionDown = MoveTo::create(0.5, Vec2(U::cx + 20, U::cy + 80 - 70));
	seq = Sequence::createWithTwoActions(
		EaseSineIn::create(actionUp),
		EaseSineOut::create(actionDown)
		);
	repeat = RepeatForever::create(seq);
	labelNum->runAction(repeat);
}
