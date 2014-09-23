#pragma once
#include "Util.h"
#include "Common/Block.h"

class ChapterScene : public Scene
{
public:
    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    CREATE_FUNC(ChapterScene);

private:
	Vector<Block *> m_blocks;
};

