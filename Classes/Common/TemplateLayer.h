#pragma once
#include "Util.h"

class TemplateLayer : public CCLayer
{
public:
    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    CREATE_FUNC(TemplateLayer);
};

