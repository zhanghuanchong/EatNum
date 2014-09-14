#include "HomeSettingMenu.h"
#include "../Setting/SettingScene.h"

HomeSettingMenu * HomeSettingMenu::create()
{
	HomeSettingMenu *pRet = new HomeSettingMenu();
    if (pRet && pRet->initWithArray())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool HomeSettingMenu::initWithArray()
{
	CCSize size = Util::size;
	CCMenuItemSprite *btnSetting = CCMenuItemSprite::create
	(
		CCSprite::createWithSpriteFrameName("setting.png"),
		CCSprite::createWithSpriteFrameName("settingActive.png"),
		this,
		menu_selector(HomeSettingMenu::changeSetting)
	);
	btnSetting->setPositionX(size.width / 2 - 100);
	CCMenuItemSprite *btnFavorite = CCMenuItemSprite::create
	(
		CCSprite::createWithSpriteFrameName("favorite.png"),
		CCSprite::createWithSpriteFrameName("favoriteActive.png"),
		this,
		menu_selector(HomeSettingMenu::addFavorite)
	);
	btnFavorite->setPositionX(-size.width / 2 + 100);
	CCArray *btns = CCArray::create(btnSetting, btnFavorite, NULL);
	bool bRet = CCMenu::initWithArray(btns);
	if (bRet)
	{
	}
	return bRet;
}

void HomeSettingMenu::changeSetting( CCObject *sender )
{
	Util::pushWoodScene(SettingScene::create());
}

void HomeSettingMenu::addFavorite( CCObject *sender )
{

}
