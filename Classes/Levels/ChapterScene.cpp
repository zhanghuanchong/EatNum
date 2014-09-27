#include "ChapterScene.h"
#include "Home/HomeScene.h"
#include "Common/ScalableSprite.h"
#include "Common/Block.h"
#include "Levels/LevelsScene.h"

bool ChapterScene::init()
{
    if ( !Scene::init() )
    {
        return false;
	}

	auto bgLayer = LayerColor::create(Color4B(230, 142, 79, 255));
	this->addChild(bgLayer);

	auto label = U::label("Select Chapter", 50, 1);
	label->setPosition(U::cx, U::height * .85);
	this->addChild(label);

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [](){
		Util::director->replaceScene(TransitionSlideInL::create(0.2f, HomeScene::create()));
	});
	btnPlay->setPosition(U::cx, 120);
	this->addChild(btnPlay);

	int count = Util::getChapterCount();
	for (int i = 0; i < count; i++)
	{
		Block *block = Block::create(Color4B(180,179,85, 255), to_string(i + 1), [i, this](Ref* pSender){
			this->gotoChapter(i);
		});
		float x = U::cx + ((i % 2) * 2 - 1) * 55;
		float y = U::cy + ((count - 1 - i) / 2 - 1.5) * 110;
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
