#include "LevelsScene.h"

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
	auto ret = Scene::init();

	return ret;
}

void LevelsScene::onEnterTransitionDidFinish()
{

}
