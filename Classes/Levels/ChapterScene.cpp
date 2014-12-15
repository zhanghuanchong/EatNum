#include "ChapterScene.h"
#include "../Home/HomeScene.h"
#include "../Common/ScalableSprite.h"
#include "../Common/Block.h"
#include "../Common/BaseScene.h"
#include "../Levels/LevelsScene.h"

bool ChapterScene::init()
{
    if ( !BaseScene::init() )
    {
        return false;
	}

	auto bgLayer = LayerColor::create(Color4B(230, 142, 79, 255));
	this->addChild(bgLayer);

	auto label = U::label("Select Chapter", 50, 1);
	label->setPosition(U::cx, U::height * .82);
	this->addChild(label);

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [](){
		Util::director->replaceScene(TransitionSlideInL::create(0.2f, HomeScene::create()));
	});
	btnPlay->setPosition(U::cx, 120);
	this->addChild(btnPlay);

	int currentChapter = U::userDefault->getIntegerForKey("currentChapter", 0);

	int count = Util::getChapterCount();
	for (int i = 0; i < count; i++)
	{
		Block *block = Block::create(Color4B(158, 74, 47, 255), to_string(i + 1), [i, this](Ref* pSender, Touch *, Event *){
			this->gotoChapter(i);
		});
		if (i > currentChapter)
		{
			block->lock(true);
		}
		float x = U::cx + ((i % 2) * 2 - 1) * 55;
		float y = U::cy + ((7 - i) / 2 - 1.5) * 110;
		block->setPosition(x, y);
		this->addChild(block);
	}

    return true;
}

void ChapterScene::gotoChapter(int i)
{
	LevelsScene *ls = LevelsScene::createWithChapter(i);
	Util::director->replaceScene(TransitionSlideInR::create(0.2f, ls));
}
