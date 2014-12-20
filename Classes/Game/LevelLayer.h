#pragma once
#include "Util.h"
#include "../Common/ScalableSprite.h"

class LevelLayer : public Layer
{
public:
	static LevelLayer *create(const Color4B &color, Sprite *btnLeft, Sprite *btnRight, Sprite *btnAdditional = nullptr);

	virtual bool init(const Color4B &color, Sprite *btnLeft, Sprite *btnRight, Sprite *btnAdditional = nullptr);
    virtual void onEnter();

CC_CONSTRUCTOR_ACCESS:
	LevelLayer() : 
		m_btnLeft(nullptr),
		m_btnRight(nullptr),
		m_bgLayer(nullptr),
		m_btnAdditional(nullptr) {}

private:
	LayerColor *m_bgLayer;
	Sprite *m_btnLeft;
	Sprite *m_btnRight;
	Sprite *m_btnAdditional;
	ScalableSprite *m_share;
	ScalableSprite *m_favorite;
	ScalableSprite *m_gameCenter;
};

