#pragma once
#include "Util.h"

class HomeSettingMenu :
	public CCMenu
{	
public:
	static HomeSettingMenu *create();

	virtual bool initWithArray();

	virtual void changeSetting(CCObject *sender);
	virtual void addFavorite(CCObject *sender);

};

