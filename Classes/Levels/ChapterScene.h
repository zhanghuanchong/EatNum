#pragma once
#include "Util.h"

class ChapterScene : public Scene
{
public:
    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    CREATE_FUNC(ChapterScene);
};

