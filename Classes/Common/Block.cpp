#include "Block.h"

Block* Block::create(const Color4B& bgColor, 
	const string& title, 
	const touchCallback& onTouchEnd,
	const Color4B& titleColor /*= Color4B::WHITE*/, 
	const Size& size /*= Size(100, 100)*/, 
	const bool interactive /*= true*/, 
	const bool shader/* = true*/,
	const touchCallback& onTouchBegan/* = nullptr*/,
	const touchCallback& onTouchMoved/* = nullptr*/,
	const touchCallback& onTouchCancelled/* = nullptr*/)
{
	Block *sprite = new (std::nothrow) Block();
	if (sprite && sprite->init(bgColor, title, onTouchEnd, titleColor, size, 
		interactive, shader, onTouchBegan, onTouchMoved, onTouchCancelled))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Block::init(const Color4B& bgColor, 
	const string& title, 
	const touchCallback& onTouchEnd,
	const Color4B& titleColor, 
	const Size& size, 
	const bool interactive, 
	const bool shader,
	const touchCallback& onTouchBegan,
	const touchCallback& onTouchMoved,
	const touchCallback& onTouchCancelled)
{
	auto ret = Node::init();
	this->setContentSize(size);
	this->setAnchorPoint(Vec2(.5f, .5f));

	m_card = Node::create();
	m_card->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_card->setPosition(size.width / 2, size.height / 2);
	this->addChild(m_card, 1);

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
	m_bg->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_card->addChild(m_bg, 0);

	// Add title
	m_title = U::labelWithoutTranslate(title, 60.0f);
	m_title->setAnchorPoint(Vec2(0.5f, 0.65f));
	m_title->setTextColor(titleColor);
	m_card->addChild(m_title, 1);

	if (shader)
	{
		// Add shader
		m_shader = Sprite::create();
		Color4B color(0, 0, 0, 100);
		buffer = (GLubyte *)malloc(sizeof(GLubyte)* 4);
		buffer[0] = color.r;
		buffer[1] = color.g;
		buffer[2] = color.b;
		buffer[3] = color.a;

		tex = new Texture2D();
		tex->initWithData(buffer, sizeof(GLubyte)* 4, Texture2D::PixelFormat::RGBA8888, 1, 1, size);
		m_shader->setTexture(tex);
		m_shader->setTextureRect(Rect(0, 0, size.width, size.height));
		m_shader->setAnchorPoint(Vec2(0.5f, 0.5f));
		m_shader->setPosition(size.width / 2 + 2, size.height / 2 - 2);
		this->addChild(m_shader, 0);
	}

	if (interactive)
	{
		// Touch event listener
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [onTouchBegan, this, size](Touch *touch, Event *event) {
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			if (rect.containsPoint(locationInNode)) {
				this->m_bClicked = false;
				Vector<FiniteTimeAction *> actions;
				actions.pushBack(EaseSineOut::create(ScaleTo::create(0.1f, 1.3f)));
				actions.pushBack(EaseSineOut::create(MoveTo::create(0.1f, Vec2(size.width / 2 - 5, size.height / 2 + 5))));
				Spawn *spawn = Spawn::create(actions);
				this->m_card->runAction(spawn);

				Vector<FiniteTimeAction *> actions2;
				actions2.pushBack(EaseSineOut::create(ScaleTo::create(0.1f, 1.35f)));
				actions2.pushBack(EaseSineOut::create(MoveTo::create(0.1f, Vec2(size.width / 2 + 5, size.height / 2 - 5))));
				this->m_shader->runAction(Spawn::create(actions2));

				this->m_oldZOrder = this->getLocalZOrder();
				this->setLocalZOrder(100);

				if (onTouchBegan)
				{
					onTouchBegan(this, touch, event);
				}

				return true;
			}
			return false;
		};
		listener->onTouchMoved = [onTouchMoved, this](Touch *touch, Event *event) {
			if (onTouchMoved)
			{
				onTouchMoved(this, touch, event);
			}
		};
		listener->onTouchEnded = [onTouchEnd, this, size](Touch *touch, Event *event) {
			if (this->m_bClicked)
			{
				return;
			}
			this->m_bClicked = true;
			Vector<FiniteTimeAction *> actions;
			actions.pushBack(EaseSineOut::create(ScaleTo::create(0.1f, 1.0f)));
			actions.pushBack(EaseSineOut::create(MoveTo::create(0.1f, Vec2(size.width / 2, size.height / 2))));
			Spawn *spawn = Spawn::create(actions);

			Vector<FiniteTimeAction *> actionSequence;
			actionSequence.pushBack(spawn);
			actionSequence.pushBack(CallFunc::create([onTouchEnd, touch, event, this](){
				if (onTouchEnd)
				{
					onTouchEnd(this, touch, event);
				}
				this->m_bClicked = false;

				this->setLocalZOrder(this->m_oldZOrder);
			}));
			this->m_card->runAction(Sequence::create(actionSequence));

			Vector<FiniteTimeAction *> actions2;
			actions2.pushBack(EaseSineOut::create(ScaleTo::create(0.1f, 1.0f)));
			actions2.pushBack(EaseSineOut::create(MoveTo::create(0.1f, Vec2(size.width / 2 + 2, size.height / 2 - 2))));
			this->m_shader->runAction(Spawn::create(actions2));
		};
		listener->onTouchCancelled = [onTouchCancelled, this](Touch *touch, Event *event) {
			if (onTouchCancelled)
			{
				onTouchCancelled(this, touch, event);
			}
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}

	return ret;
}
