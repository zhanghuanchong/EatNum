#pragma once
#include "Util.h"
#include "../Common/ScalableSprite.h"

class LevelLayer : public Layer
{
public:
	static LevelLayer *create(const Color4B &color, Sprite *btnLeft, Sprite *btnRight);

	virtual bool init(const Color4B &color, Sprite *btnLeft, Sprite *btnRight);
    virtual void onEnter();

CC_CONSTRUCTOR_ACCESS:
	LevelLayer() : 
		m_btnLeft(nullptr),
		m_btnRight(nullptr),
		m_bgLayer(nullptr) {}

private:
	LayerColor *m_bgLayer;
	Sprite *m_btnLeft;
	Sprite *m_btnRight;
	ScalableSprite *m_share;
	ScalableSprite *m_favorite;
	ScalableSprite *m_gameCenter;
};

