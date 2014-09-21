#pragma once

#include "Util.h"

class HomeScene : public Scene
{
public:
    virtual bool init();
	virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);

private:
	Label *labelNom;
	Label *labelNum;
};

