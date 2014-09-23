#pragma once
#include "Util.h"

class Block : public Node
{
public:
	static Block* create(const Color4B& bgColor, const string& title, const std::function<void()>& onTouchEnd,
		const Color4B& titleColor = Color4B::WHITE, const Size& size = Size(100, 100));

CC_CONSTRUCTOR_ACCESS:
	Block() : m_bg(nullptr), m_title(nullptr), m_bClicked(false) {}
	virtual ~Block() {}

	virtual bool init(const Color4B& bgColor, const string& title, const std::function<void()>& onTouchEnd, 
		const Color4B& titleColor, const Size& size);

private:
	Sprite *m_bg;
	Label *m_title;
	bool m_bClicked;
	CC_DISALLOW_COPY_AND_ASSIGN(Block);
};

