#pragma once
#include "Util.h"

class HomeMenu :
	public CCMenu
{	
public:
	static HomeMenu *create();

	virtual bool initWithArray();

	virtual void startGame(CCObject *sender);
	virtual void inviteFriends(CCObject *sender);
	virtual void gainFreeCoins(CCObject *sender);
};

