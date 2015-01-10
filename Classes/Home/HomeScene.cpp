#include "HomeScene.h"
#include "../Levels/ChapterScene.h"
#include "../Common/ScalableSprite.h"
#include "../Game/GameScene.h"
#include "../About/AboutScene.h"

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

	m_share = ScalableSprite::create("share_50.png", [](){
        Util::crossHelper->showActivities();
	});
	m_share->setPosition(10, 10);
	m_share->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_share, 1000);
    
    m_gamecenter = ScalableSprite::create("gamecenter_50.png", [](){
        Util::crossHelper->showGameCenter();
    });
    m_gamecenter->setPosition(90, 10);
    m_gamecenter->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_gamecenter, 1000);

	m_about = ScalableSprite::create("about.png", [this](){
		Util::director->replaceScene(TransitionFlipX::create(0.3f, AboutScene::create()));
	});
	m_about->setPosition(170, 10);
	m_about->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_about, 1000);
    
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
