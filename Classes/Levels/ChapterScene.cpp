#include "ChapterScene.h"
#include "Home/HomeScene.h"

bool ChapterScene::init()
{
    if ( !Scene::init() )
    {
        return false;
	}

	auto bgLayer = LayerColor::create(Color4B(230, 142, 79, 255));
	this->addChild(bgLayer);

	auto label = U::label("Select Chapter", 50, 1);
	label->setPosition(U::cx, U::height * .8);
	this->addChild(label);

	MenuItemImage *miReturn = MenuItemImage::create("back.png", "back.png", [&](Ref *){
		Util::director->replaceScene(TransitionSlideInL::create(0.2, HomeScene::create()));
	});
	Menu *menu = Menu::createWithItem(miReturn);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(U::cx, 120);
	this->addChild(menu);

    return true;
}

void ChapterScene::onEnterTransitionDidFinish()
{

}
