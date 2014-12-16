#include "DraggableBlock.h"

DraggableBlock* DraggableBlock::create(const Color4B& bgColor,
	const string& title, 
	const touchCallback& onTouchBegan /*= nullptr*/, 
	const touchCallback& onTouchMoved /*= nullptr*/, 
	const touchCallback& onTouchEnd /*= nullptr*/, 
	const touchCallback& onTouchCancelled /*= nullptr*/)
{
	DraggableBlock *sprite = new (std::nothrow) DraggableBlock();
	if (sprite && sprite->init(bgColor, title, 
		onTouchBegan, onTouchMoved, onTouchEnd, onTouchCancelled))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool DraggableBlock::init(const Color4B& bgColor,
	const string& title, 
	const touchCallback& onTouchBegan, 
	const touchCallback& onTouchMoved, 
	const touchCallback& onTouchEnd, 
	const touchCallback& onTouchCancelled)
{
	return Block::init(bgColor, 
		title, 
		onTouchEnd, 
		Color4B::WHITE, 
		cocos2d::Size(100, 100), 
		true, 
		true, 
		[onTouchBegan, this](Ref *pSender, Touch *touch, Event *event) {
			cocos2d::Point currentPoint = this->getPosition();
			this->m_dragStartPoint = currentPoint;

			cocos2d::Point touchPoint = touch->getLocation();
			this->m_dragStartDistance = cocos2d::Point(touchPoint.x - currentPoint.x, 
				touchPoint.y - currentPoint.y);

			if (onTouchBegan)
			{
				onTouchBegan(this, touch, event);
			}
		}, 
		[onTouchMoved, this](Ref *pSender, Touch *touch, Event *event) {
			if (this->isDropped())
			{
				return;
			}
			cocos2d::Point touchPoint = touch->getLocation();
			this->setPosition(cocos2d::Point(touchPoint.x - this->m_dragStartDistance.width,
				touchPoint.y - this->m_dragStartDistance.height));

			if (onTouchMoved)
			{
				onTouchMoved(this, touch, event);
			}
		},
		[onTouchCancelled, this](Ref *pSender, Touch *touch, Event *event) {
			this->setPosition(this->m_dragStartPoint);

			if (onTouchCancelled)
			{
				onTouchCancelled(this, touch, event);
			}
		});
}

void DraggableBlock::revert()
{
	this->moveTo(m_dragStartPoint);
}

void DraggableBlock::moveTo(cocos2d::Point &newPoint, float interval/* = 0.2f */)
{
	MoveTo *move = MoveTo::create(interval, newPoint);
	EaseSineInOut *ease = EaseSineInOut::create(move);
	this->runAction(ease);
}

void DraggableBlock::setTitle(const string &newTitle)
{
	Block::setTitle(newTitle);

}

int DraggableBlock::getValue()
{
	const std::string &v = this->getTitle();
	if (v.length() <= 0)
	{
		return -1;
	}
	return atoi(v.c_str());
}

void DraggableBlock::decrease()
{
	int v = this->getValue();
	if (v <= 0)
	{
		return;
	}
	else if (v == 1)
	{
		v = 0;
	}
	else
	{
		v -= 2;
	}
	this->updateValue(v);
}

void DraggableBlock::updateValue(int newValue)
{
	this->setTitle(to_string(newValue));
    Color4B color = U::getColorOfBlockValue(newValue);
	this->setBgColor(color);

	if (newValue == 0)
	{
		this->getEventDispatcher()->removeEventListenersForTarget(this);
	}
}
