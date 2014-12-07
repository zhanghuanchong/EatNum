#include "ScalableSprite.h"

ScalableSprite* ScalableSprite::create(const std::string& filename, const std::function<void()>& onTouchEnd)
{
	ScalableSprite *sprite = new (std::nothrow) ScalableSprite();
	if (sprite && sprite->initWithFile(filename, onTouchEnd))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool ScalableSprite::initWithFile(const std::string& filename, const std::function<void()>& onTouchEnd)
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
	listener->onTouchEnded = [onTouchEnd, this](Touch *touch, Event *event) {
		if (this->m_bClicked)
		{
			return;
		}
		this->m_bClicked = true;
		Vector<FiniteTimeAction *> actions;
		actions.pushBack(EaseSineOut::create(ScaleTo::create(0.1f, 1.5f)));
		actions.pushBack(EaseSineIn::create(ScaleTo::create(0.1f, 1.0f)));
		actions.pushBack(DelayTime::create(0.1f));
		actions.pushBack(CallFunc::create([onTouchEnd, this](){
			U::playEffect();
			if (onTouchEnd)
			{
				onTouchEnd();
			}
			this->m_bClicked = false;
		}));
		this->runAction(Sequence::create(actions));
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return ret;
}
