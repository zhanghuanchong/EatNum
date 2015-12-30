# EatNum Game

Developed with Cocos2d-x v3.2, by Hans Zhang (ezburg@gmail.com).

### [Download and play](http://wuruihong.com/?p=46)

## C++11 feature: Lambda

###

```c++
btnNext = ScalableSprite::create("next.png", 
	[this, nextChapter, nextLevel, showNext]() {
		m_doneLayer->removeFromParent();
		m_doneLayer = nullptr;
		m_nChapter = nextChapter;
		m_nLevel = nextLevel;
		this->loadLevel();
		this->scaleBlocks(0);
	}
);
```

## STL std:function

```c++
typedef std::function<void(Ref *, Touch *, Event *)> touchCallback;
```

## Customized Node

```c++
class Block : public Node
{
CC_CONSTRUCTOR_ACCESS:
	virtual ~Block() {}

	virtual bool init(const Color4B& bgColor, 
		const string& title, 
		const touchCallback& onTouchEnd,
		const touchCallback& onTouchBegan,
		const touchCallback& onTouchMoved,
		const touchCallback& onTouchCancelled);
};

```

And its sub class:

```c++
class DraggableBlock : public Block
{
	// ...
};
```

## Cross platform support classes

* CrossHelper
* CrossiOS
* CrossAndroid

## Simple Cocos2d-x Class generator

Run on windows:
> Classes/CreateCocos2dxClass.exe