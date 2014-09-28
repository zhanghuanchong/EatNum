#pragma once
#include "Util.h"

class GameScene : public Scene
{
public:
	static GameScene *createWithLevel(int level, int chapter);

CC_CONSTRUCTOR_ACCESS:
	GameScene() :
		m_nChapter(0),
		m_nLevel(0) {}

	virtual bool initWithLevel(int level, int chapter);
	virtual bool init();
	virtual void onEnterTransitionDidFinish();

private:
	int m_nChapter;
	int m_nLevel;
};

