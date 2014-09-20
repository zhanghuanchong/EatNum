#pragma once

#include "Util.h"

class LevelsScene : public Scene
{
public:
    virtual bool init();
	virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
	CREATE_FUNC(LevelsScene);
};

