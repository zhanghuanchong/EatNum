#pragma once
#include "Block.h"

class DraggableBlock : public Block
{
public:
	static DraggableBlock* create(const Color4B& bgColor,
		const string& title,
		const touchCallback& onTouchBegan = nullptr,
		const touchCallback& onTouchMoved = nullptr,
		const touchCallback& onTouchEnd = nullptr,
		const touchCallback& onTouchCancelled = nullptr);

CC_CONSTRUCTOR_ACCESS:
	DraggableBlock() :
		m_dragStartPoint(0, 0),
		m_dragStartDistance(0, 0) {}
	virtual ~DraggableBlock() {}

	virtual bool init(const Color4B& bgColor,
		const string& title,
		const touchCallback& onTouchBegan,
		const touchCallback& onTouchMoved,
		const touchCallback& onTouchEnd,
		const touchCallback& onTouchCancelled);

private:
	Size m_dragStartDistance;
	Point m_dragStartPoint;
	CC_DISALLOW_COPY_AND_ASSIGN(DraggableBlock);
};

