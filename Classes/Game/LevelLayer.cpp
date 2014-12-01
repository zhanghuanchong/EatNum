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
	if (!Layer::init())
	{
		return false;
	}
	m_btnLeft = btnLeft;
	m_btnRight = btnRight;

	m_bgLayer = LayerColor::create(color);
	this->addChild(m_bgLayer);
	m_bgLayer->setVisible(false);
	
	m_btnLeft->setPosition(-45, U::cy);
	this->addChild(m_btnLeft);
	
	m_btnRight->setPosition(U::width + 45, U::cy);
	this->addChild(m_btnRight);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch *touch, Event *event) {
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void LevelLayer::onEnter()
{
	Layer::onEnter();

	Sequence *seq = Sequence::createWithTwoActions(DelayTime::create(0.5), CallFunc::create([this](){
		m_bgLayer->setVisible(true);

		m_btnLeft->runAction(EaseSineOut::create(MoveTo::create(0.2f, Vec2(U::cx - 90, U::cy))));
		m_btnRight->runAction(EaseSineOut::create(MoveTo::create(0.2f, Vec2(U::cx + 90, U::cy))));
	}));
	this->runAction(seq);
}