#include "HomeScene.h"
#include "Levels/ChapterScene.h"
#include "Common/ScalableButton.h"

bool HomeScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
	auto bgLayer = LayerColor::create(Color4B(195, 75, 134, 255));
	this->addChild(bgLayer);

	labelNom = U::label("NOM", 100, 1);
	labelNom->setPosition(U::cx - 20, U::cy + 70);
	this->addChild(labelNom);

	labelNum = U::label("NUM", 100, 1);
	labelNum->setPosition(U::cx + 20, U::cy - 70);
	this->addChild(labelNum);

	ScalableButton *btnPlay = ScalableButton::create("play.png", [](){
		Util::director->replaceScene(TransitionSlideInR::create(0.2f, ChapterScene::create()));
	});
	btnPlay->setPosition(U::cx, 120);
	this->addChild(btnPlay);

	/*Sprite *btnPlay = Sprite::create("play.png");
	btnPlay->setPosition(U::cx, 120);
	this->addChild(btnPlay);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [btnPlay](Touch *touch, Event *event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		return rect.containsPoint(locationInNode);
	};
	listener->onTouchEnded = [](Touch *touch, Event *event) {
		Util::director->replaceScene(TransitionSlideInR::create(0.2f, ChapterScene::create()));
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, btnPlay);*/
    
    return true;
}

void HomeScene::onEnterTransitionDidFinish()
{
	MoveTo *actionDown = MoveTo::create(0.5, Vec2(U::cx - 20, U::cy + 40));
	MoveTo *actionUp = MoveTo::create(0.5, Vec2(U::cx - 20, U::cy + 70));
	Sequence *seq = Sequence::createWithTwoActions(
		EaseSineIn::create(actionDown),
		EaseSineOut::create(actionUp)
	);
	RepeatForever *repeat = RepeatForever::create(seq);
	labelNom->runAction(repeat);

	actionUp = MoveTo::create(0.5, Vec2(U::cx + 20, U::cy - 40));
	actionDown = MoveTo::create(0.5, Vec2(U::cx + 20, U::cy - 70));
	seq = Sequence::createWithTwoActions(
		EaseSineIn::create(actionUp),
		EaseSineOut::create(actionDown)
		);
	repeat = RepeatForever::create(seq);
	labelNum->runAction(repeat);
}
