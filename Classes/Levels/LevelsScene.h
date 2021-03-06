#pragma once

#include "Util.h"
#include "../Common/BaseScene.h"

class LevelsScene : public BaseScene
{
public:
	static LevelsScene *createWithChapter(int chapter);

CC_CONSTRUCTOR_ACCESS:
	LevelsScene() :
		m_nChapter(0) {}

	virtual bool initWithChapter(int chapter);
	virtual bool init();

private:
	int m_nChapter;
};

