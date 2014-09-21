#pragma once
#include "Util.h"

class ScalableButton : public Sprite
{
public:
	static ScalableButton* create(const std::string& filename, const std::function<void()>& onTouchEnd);

CC_CONSTRUCTOR_ACCESS:
	ScalableButton() {}
	virtual ~ScalableButton() {}

	virtual bool initWithFile(const std::string& filename, const std::function<void()>& onTouchEnd);

private:
	CC_DISALLOW_COPY_AND_ASSIGN(ScalableButton);
};

