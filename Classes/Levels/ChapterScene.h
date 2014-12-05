#pragma once
#include "Util.h"
#include "Common/Block.h"
#include "Common/BaseScene.h"

class ChapterScene : public BaseScene
{
public:
    virtual bool init();

    CREATE_FUNC(ChapterScene);

private:
	void gotoChapter(int i);
};

