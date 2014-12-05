#include "LevelLayer.h"
#include "Common/ScalableSprite.h"

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

	m_share = ScalableSprite::create("share.png", [](){

	});
	m_share->setPosition(U::width - 10, 10);
	m_share->setAnchorPoint(Vec2(1, 0));
	this->addChild(m_share, 1000);

	m_favorite = ScalableSprite::create("favorite.png", [](){

	});
	m_favorite->setPosition(U::width - 78, 10);
	m_favorite->setAnchorPoint(Vec2(1, 0));
	this->addChild(m_favorite, 1000);

	m_gameCenter = ScalableSprite::create("gamecenter.png", [](){

	});
	m_gameCenter->setPosition(U::width - 146, 10);
	m_gameCenter->setAnchorPoint(Vec2(1, 0));
	this->addChild(m_gameCenter, 1000);

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