#include "SettingScene.h"
#include "SettingLayer.h"
#include "SettingAboutLayer.h"

bool SettingScene::init()
{
	bool bRet = WoodScene::init();
	if (bRet)
	{
		CCSize size = Util::size;

		SettingLayer *layer = SettingLayer::create();
		this->addChild(layer);
		layer->setPosition(ccp(size.width / 2, size.height * 0.85));

		SettingAboutLayer *aboutLayer = SettingAboutLayer::create();
		this->addChild(aboutLayer);
		aboutLayer->setPosition(ccp(size.width / 2, 0));
	}
	return bRet;
}

void SettingScene::onEnterTransitionDidFinish()
{
	this->showBackButton(true);
}
