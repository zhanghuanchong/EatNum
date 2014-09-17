#include "HomeScene.h"

bool HomeScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
	auto bgLayer = LayerColor::create(Color4B(195, 75, 134, 255));
	this->addChild(bgLayer);

	auto labelNom = U::label("NOM", 120, 1);
	labelNom->setPosition(U::cx - 20, U::cy + 70);
	this->addChild(labelNom);

	auto labelNum = U::label("NUM", 120, 1);
	labelNum->setPosition(U::cx + 20, U::cy - 70);
	this->addChild(labelNum);

    /*auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HomeScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

    auto sprite = Sprite::create("HomeScene.png");

    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);*/
    
    return true;
}


void HomeScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
