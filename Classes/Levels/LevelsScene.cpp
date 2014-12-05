#include "LevelsScene.h"
#include "Common/Block.h"
#include "Common/ScalableSprite.h"
#include "Levels/ChapterScene.h"
#include "Game/GameScene.h"

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
	label->setPosition(U::cx, U::height * .82);
	this->addChild(label);

	stringstream s;
	s << U::t("Chapter") << " " << this->m_nChapter + 1;

	auto labelChapter = U::labelWithoutTranslate(s.str(), 35, 1);
	labelChapter->setPosition(U::cx - 270, U::cy + 230);
	labelChapter->setAnchorPoint(Vec2(0, 0));
	this->addChild(labelChapter);

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [](){
		Util::director->replaceScene(TransitionSlideInL::create(0.2f, ChapterScene::create()));
	});
	btnPlay->setPosition(U::cx, 120);
	this->addChild(btnPlay);

	int currentChapter = U::userDefault->getIntegerForKey("currentChapter", 0);
	int currentLevel = U::userDefault->getIntegerForKey("currentLevel", 0);

	int count = Util::getLevelCount(this->m_nChapter);
	for (int i = 0; i < count; i++)
	{
		Block *block = Block::create(Color4B(180, 179, 85, 255), to_string(i + 1), [i, this](Ref* pSender, Touch *, Event *){
			GameScene *ls = GameScene::createWithLevel(i, this->m_nChapter);
			Util::director->replaceScene(TransitionFade::create(0.5f, ls));
		});
		if ((this->m_nChapter == currentChapter && i > currentLevel) || this->m_nChapter > currentChapter)
		{
			block->lock(true);
		}
		float x = U::cx + ((i % 5) * 2 - 4) * 55;
		float y = U::cy + ((19 - i) / 5 - 1.5) * 110;
		block->setPosition(x, y);
		this->addChild(block);
	}

	return true;
}
