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
	if (!Scene::init())
	{
		return false;
	}

	auto bgLayer = LayerColor::create(Color4B(97, 112, 116, 255)); //92,106,110
	this->addChild(bgLayer);

	stringstream s;
	s << U::t("Level") << " " << this->m_nChapter + 1 << " - " << this->m_nLevel + 1;

	auto label = U::labelWithoutTranslate(s.str(), 35, 1);
	label->setPosition(U::width - 20, U::height - 30);
	label->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(label, 1001);

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [this](){
		Util::director->replaceScene(TransitionFade::create(0.5f, LevelsScene::createWithChapter(this->m_nChapter)));
	});
	btnPlay->setPosition(U::cx - 80, 50);
	this->addChild(btnPlay, 1001);

	ScalableSprite *btnReload = ScalableSprite::create("reload.png", [this](){
		this->initBlocks();
	});
	btnReload->setPosition(U::cx + 80, 50);
	this->addChild(btnReload);

	int x = U::cx - 2 * 100 - 50 - 2 * 10;
	int y = U::cy - 3 * 100 - 2 * 10 - 5;
	int yj = y;
	for (int i = 0; i < 6; i++)
	{
		yj += 110;
		int xj = x;
		for (int j = 0; j < 5; j++)
		{
			Block *block = Block::create(Color4B(92, 106, 110, 255), "", nullptr, Color4B::WHITE, Size(100, 100), false, false);
			block->setPosition(xj + 50, yj - 60);
			this->addChild(block, 0);

			xj += 110;
		}
	}

	rapidjson::Value& levelData = U::getLevel(m_nChapter, m_nLevel);
	if (levelData.HasMember("tip"))
	{
		const char* tip = levelData["tip"].GetString();
		auto tipLabel = U::label(tip, 45, 1);
		tipLabel->setHorizontalAlignment(TextHAlignment::CENTER);
		tipLabel->setVerticalAlignment(TextVAlignment::TOP);
		tipLabel->setDimensions(U::width, yj - 30);
		tipLabel->setPosition(U::cx, (yj - 30) / 2);
		this->addChild(tipLabel, 1000);
	}

	this->initBlocks();

    return true;
}

void GameScene::initBlocks()
{
	for (unsigned i = 0; i < m_blocks.size(); i++)
	{
		Block *block = m_blocks.at(i);
		block->removeFromParentAndCleanup(true);
	}

	rapidjson::Value& levelData = U::getLevel(m_nChapter, m_nLevel);
	int x = U::cx - 2 * 100 - 50 - 2 * 10;
	int y = U::cy + 3 * 100 + 2 * 10 + 5;

	if (levelData.HasMember("cells") && levelData["cells"].IsArray())
	{
		for (unsigned i = 0; i < levelData["cells"].Size(); i++)
		{
			rapidjson::Value& cell = levelData["cells"][i];
			if (cell.HasMember("x") && cell.HasMember("y") && cell.HasMember("v"))
			{
				int _x = cell["x"].GetInt();
				int _y = cell["y"].GetInt();
				int _v = cell["v"].GetInt();

				Block *block;
				if (_v > 0)
				{
					block = Block::create(U::getColorOfBlockValue(_v), to_string(_v), nullptr, Color4B::WHITE, Size(100, 100));
				}
				else if (_v == 0)
				{
					block = Block::create(Color4B::BLACK, to_string(_v), nullptr, Color4B::WHITE, Size(100, 100), false);
				}
				else
				{
					block = Block::create(Color4B(102, 102, 102, 255), "", nullptr, Color4B::WHITE, Size(100, 100), false);
				}
				block->setPosition(x + _x * 110 + 50, y - _y * 110 - 50);
				this->addChild(block, 10);
				this->m_blocks.pushBack(block);

				/*auto listener = EventListenerTouchOneByOne::create();
				listener->setSwallowTouches(true);
				listener->onTouchBegan = [block](Touch *touch, Event *event) {
				return true;
				};
				listener->onTouchMoved = [block](Touch *touch, Event *event) {
				block->setPosition(touch->getLocation());
				};
				block->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, block);*/
			}
		}
	}
}

void GameScene::onEnterTransitionDidFinish()
{

}
