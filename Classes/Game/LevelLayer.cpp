#include "LevelLayer.h"

LevelLayer * LevelLayer::create(const Color4B &color, Sprite *btnLeft, Sprite *btnRight)
{
	LevelLayer *sprite = new (std::nothrow) LevelLayer();
	if (sprite && sprite->init(color, btnLeft, btnRight))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}


bool LevelLayer::init(const Color4B &color, Sprite *btnLeft, Sprite *btnRight)
{
	if (!LayerColor::initWithColor(color))
	{
		return false;
	}
	m_btnLeft = btnLeft;
	m_btnRight = btnRight;
	
	m_btnLeft->setPosition(-45, U::cy);
	this->addChild(m_btnLeft);
	
	m_btnRight->setPosition(U::width + 45, U::cy);
	this->addChild(m_btnRight);

	return true;
}

void LevelLayer::onEnter()
{
	LayerColor::onEnter();

	m_btnLeft->runAction(EaseSineOut::create(MoveTo::create(0.2, Vec2(U::cx - 90, U::cy))));
	m_btnRight->runAction(EaseSineOut::create(MoveTo::create(0.2, Vec2(U::cx + 90, U::cy))));
}