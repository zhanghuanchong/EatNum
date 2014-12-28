#pragma once
#include "Util.h"

class AboutScene : public Scene
{
public:
    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    CREATE_FUNC(AboutScene);
};

