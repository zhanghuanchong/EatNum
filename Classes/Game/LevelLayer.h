#pragma once
#include "Util.h"

class LevelLayer : public LayerColor
{
public:
	static LevelLayer *create(const Color4B &color, Sprite *btnLeft, Sprite *btnRight);

	virtual bool init(const Color4B &color, Sprite *btnLeft, Sprite *btnRight);
    virtual void onEnter();

CC_CONSTRUCTOR_ACCESS:
	LevelLayer() : 
		m_btnLeft(nullptr),
		m_btnRight(nullptr) {}

private:
	Sprite *m_btnLeft;
	Sprite *m_btnRight;
};

