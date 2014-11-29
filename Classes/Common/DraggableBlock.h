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

	inline Point getDragStartPoint() 
	{
		return m_dragStartPoint;
	};

	inline Size getDragStartDistance()
	{
		return m_dragStartDistance;
	};
	bool isDropped() const { return m_dropped; }
	void setDropped(bool val) { m_dropped = val; }

	void revert();
	void moveTo(Point &newPoint, float interval = 0.2f);

	virtual void setTitle(const string &newTitle);
	int getValue();
	void decrease();
	void updateValue(int newValue);

CC_CONSTRUCTOR_ACCESS:
	DraggableBlock() :
		m_dragStartPoint(0, 0),
		m_dragStartDistance(0, 0),
		m_dropped(false) {}
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
	bool m_dropped;
	CC_DISALLOW_COPY_AND_ASSIGN(DraggableBlock);
};

