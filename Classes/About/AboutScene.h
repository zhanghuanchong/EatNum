#pragma once
#include "Util.h"
#include "../Common/BaseScene.h"

class AboutScene : public BaseScene
{
public:
    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    CREATE_FUNC(AboutScene);
};

