#include "Block.h"

Block* Block::create(const Color4B& bgColor, const string& title, const std::function<void()>& onTouchEnd, 
	const Color4B& titleColor /*= Color4B::WHITE*/, const Size& size /*= Size(50, 50)*/)
{
	Block *sprite = new (std::nothrow) Block();
	if (sprite && sprite->init(bgColor, title, onTouchEnd, titleColor, size))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Block::init(const Color4B& bgColor, const string& title, const std::function<void()>& onTouchEnd, 
	const Color4B& titleColor, const Size& size)
{
	auto ret = Node::init();
	this->setContentSize(size);

	// Add block bg
	m_bg = Sprite::create();
	GLubyte *buffer = (GLubyte *)malloc(sizeof(GLubyte)* 4);
	buffer[0] = bgColor.r;
	buffer[1] = bgColor.g;
	buffer[2] = bgColor.b;
	buffer[3] = bgColor.a;

	auto tex = new Texture2D();
	tex->initWithData(buffer, sizeof(GLubyte)* 4, Texture2D::PixelFormat::RGBA8888, 1, 1, size);
	m_bg->setTexture(tex);
	m_bg->setTextureRect(Rect(0, 0, size.width, size.height));
	this->addChild(m_bg, 0);

	// Add title
	m_title = U::labelWithoutTranslate(title);
	m_title->setPosition(size.width / 2, size.height / 2);
	m_title->setTextColor(titleColor);
	this->addChild(m_title, 1);

	// Touch event listener
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
			if (onTouchEnd)
			{
				this->m_bClicked = false;
				onTouchEnd();
			}
		}));
		this->runAction(Sequence::create(actions));
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return ret;
}