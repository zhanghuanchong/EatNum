#include "LevelsScene.h"
#include "Common/Block.h"
#include "Common/ScalableSprite.h"
#include "Levels/ChapterScene.h"

LevelsScene * LevelsScene::createWithChapter(int chapter)
{
	LevelsScene *sprite = new (std::nothrow) LevelsScene();
	if (sprite && sprite->initWithChapter(chapter))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool LevelsScene::initWithChapter(int chapter)
{
	this->m_nChapter = chapter;
	return this->init();
}

bool LevelsScene::init()
{
	if (!Scene::init()) 
	{
		return false;
	}

	auto bgLayer = LayerColor::create(Color4B(115, 54, 72, 255));
	this->addChild(bgLayer);

	auto label = U::label("Select Level", 50, 1);
	label->setPosition(U::cx, U::height * .85);
	this->addChild(label);

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [](){
		Util::director->replaceScene(TransitionSlideInL::create(0.2f, ChapterScene::create()));
	});
	btnPlay->setPosition(U::cx, 120);
	this->addChild(btnPlay);

	int count = Util::getLevelCount(this->m_nChapter);
	for (int i = 0; i < count; i++)
	{
		Block *block = Block::create(Color4B(180, 179, 85, 255), to_string(i + 1), [i, this](Ref* pSender){
			
		});
		float x = U::cx + ((i % 2) * 2 - 1) * 55;
		float y = U::cy + ((count - 1 - i) / 2 - 1.5) * 110;
		block->setPosition(x, y);
		this->addChild(block);
	}

	return true;
}

void LevelsScene::onEnterTransitionDidFinish()
{
}
