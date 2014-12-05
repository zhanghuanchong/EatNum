#pragma once
#include "Util.h"
#include "ScalableSprite.h"

class BaseScene : public Scene
{
public:
    virtual bool init();

    CREATE_FUNC(BaseScene);

private:
	ScalableSprite *m_sound;
	ScalableSprite *m_music;
};

