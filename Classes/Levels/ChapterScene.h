#pragma once
#include "Util.h"
#include "Common/Block.h"

class ChapterScene : public Scene
{
public:
    virtual bool init();

    CREATE_FUNC(ChapterScene);

private:
	Vector<Block *> m_blocks;

	void gotoChapter(int i);
};
