#include "MenuItemImageScalable.h"

MenuItemImageScalable* MenuItemImageScalable::create(const std::string&normalImage, const ccMenuCallback& callback)
{
	MenuItemImageScalable *ret = new MenuItemImageScalable();
	if (ret && ret->initWithNormalImage(normalImage, callback))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool MenuItemImageScalable::initWithNormalImage(const std::string& normalImage, const ccMenuCallback& callback)
{
	auto newCallback = [this, callback](Ref *pSender)
	{
		if (this->m_bClicked)
		{
			return;
		}
		
		this->m_bClicked = true;
		Blink *blink = Blink::create(0.2, 1);
		CallFunc *func = CallFunc::create([this, callback](){
			if (callback)
			{
				callback(this);
				this->m_bClicked = false;
			}
		});
		Node *node = this->getNormalImage();
		node->runAction(Sequence::createWithTwoActions(blink, func));
	};
	return MenuItemImage::initWithNormalImage(normalImage, "", "", newCallback);
}
