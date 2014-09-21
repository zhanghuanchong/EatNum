#include "HomeScene.h"
#include "Levels/ChapterScene.h"
#include "Common/MenuItemImageScalable.h"

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

	MenuItemImageScalable *miPlay = MenuItemImageScalable::create("play.png", [&](Ref *){
		Util::director->replaceScene(TransitionSlideInR::create(0.2f, ChapterScene::create()));
	});
	Menu *menu = Menu::createWithItem(miPlay);
	menu->setAnchorPoint(Vec2(0.5f, 0.5f));
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(U::cx, 120);
	this->addChild(menu);
    
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
