#pragma once
#include "Util.h"

class MenuItemImageScalable : public MenuItemImage
{
public:
	static MenuItemImageScalable* create(const std::string&normalImage, const ccMenuCallback& callback);

CC_CONSTRUCTOR_ACCESS:
	
	MenuItemImageScalable() : m_bClicked(false){}

	virtual ~MenuItemImageScalable(){}

	bool initWithNormalImage(const std::string& normalImage, const ccMenuCallback& callback);

private:
	bool m_bClicked;
	CC_DISALLOW_COPY_AND_ASSIGN(MenuItemImageScalable);
};

