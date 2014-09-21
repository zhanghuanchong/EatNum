#include "ScalableButton.h"

ScalableButton* ScalableButton::create(const std::string& filename, const std::function<void()>& onTouchEnd)
{
	ScalableButton *sprite = new (std::nothrow) ScalableButton();
	if (sprite && sprite->initWithFile(filename, onTouchEnd))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool ScalableButton::initWithFile(const std::string& filename, const std::function<void()>& onTouchEnd)
{
	auto ret = Sprite::initWithFile(filename);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch *touch, Event *event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		return rect.containsPoint(locationInNode);
	};
	listener->onTouchEnded = [onTouchEnd](Touch *touch, Event *event) {
		if (onTouchEnd)
		{
			onTouchEnd();
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return ret;
}
