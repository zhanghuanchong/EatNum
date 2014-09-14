#include "HomeMenu.h"
#include "../Common/WoodButton.h"

bool HomeMenu::initWithArray()
{
	WoodButton *btnStart = WoodButton::create("Start Game", this, menu_selector(HomeMenu::startGame));
	WoodButton *btnInvite = WoodButton::create("Invite Friends", this, menu_selector(HomeMenu::inviteFriends));
	WoodButton *btnCoin = WoodButton::create("Free Coins", this, menu_selector(HomeMenu::gainFreeCoins));

	CCArray *btns = CCArray::create(btnStart, btnInvite, btnCoin, NULL);
	bool bRet = CCMenu::initWithArray(btns);
	if (bRet)
	{
		this->alignItemsVerticallyWithPadding(35);
		this->setAnchorPoint(ccp(0.5, 1));
	}
	return bRet;
}

HomeMenu *HomeMenu::create()
{
	HomeMenu *pRet = new HomeMenu();
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

void HomeMenu::startGame(CCObject *sender)
{

}

void HomeMenu::inviteFriends(CCObject *sender)
{

}

void HomeMenu::gainFreeCoins(CCObject *sender)
{

}
