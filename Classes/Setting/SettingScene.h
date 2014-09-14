#pragma once
#include "Util.h"
#include "../Common/WoodScene.h"

class SettingScene :
	public WoodScene
{
public:
	CREATE_FUNC(SettingScene)

	 virtual bool init();

	virtual void onEnterTransitionDidFinish();

};

