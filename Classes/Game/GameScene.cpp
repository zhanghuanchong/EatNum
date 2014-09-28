#include "GameScene.h"
#include "Common/Block.h"
#include "Common/ScalableSprite.h"
#include "Levels/LevelsScene.h"

GameScene * GameScene::createWithLevel(int level, int chapter)
{
	GameScene *sprite = new (std::nothrow) GameScene();
	if (sprite && sprite->initWithLevel(level, chapter))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool GameScene::initWithLevel(int level, int chapter)
{
	this->m_nLevel = level;
	this->m_nChapter = chapter;
	return this->init();
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto bgLayer = LayerColor::create(Color4B(97, 112, 116, 255)); //92,106,110
	this->addChild(bgLayer);

	auto label = U::label("Level m.n", 30, 1);
	label->setPosition(U::cx, U::height * .9);
	this->addChild(label);

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [this](){
		Util::director->replaceScene(TransitionFade::create(0.5f, LevelsScene::createWithChapter(this->m_nChapter)));
	});
	btnPlay->setPosition(U::cx - 80, 50);
	this->addChild(btnPlay);

	ScalableSprite *btnReload = ScalableSprite::create("reload.png", [this](){
		
	});
	btnReload->setPosition(U::cx + 80, 50);
	this->addChild(btnReload);

	/*int count = Util::getLevelCount(this->m_nChapter);
	for (int i = 0; i < count; i++)
	{
	Block *block = Block::create(Color4B(180, 179, 85, 255), to_string(i + 1), [i, this](Ref* pSender){
	GameScene *ls = GameScene::createWithLevel(i, this->m_nChapter);
	Util::director->replaceScene(TransitionFade::create(1.0f, ls));
	});
	float x = U::cx + ((i % 5) * 2 - 4) * 55;
	float y = U::cy + ((19 - i) / 5 - 1.5) * 110;
	block->setPosition(x, y);
	this->addChild(block);
	}*/

    return true;
}

void GameScene::onEnterTransitionDidFinish()
{

}
