#pragma once
#include "Util.h"

class ScalableSprite : public Sprite
{
public:
	static ScalableSprite* create(const std::string& filename, const std::function<void()>& onTouchEnd);

CC_CONSTRUCTOR_ACCESS:
	ScalableSprite() : m_bClicked(false) {}
	virtual ~ScalableSprite() {}

	virtual bool initWithFile(const std::string& filename, const std::function<void()>& onTouchEnd);

private:
	bool m_bClicked;
	CC_DISALLOW_COPY_AND_ASSIGN(ScalableSprite);
};

