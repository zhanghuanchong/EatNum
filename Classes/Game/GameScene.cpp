#include "GameScene.h"
#include "Common/Block.h"
#include "Common/DraggableBlock.h"
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

	ScalableSprite *btnPlay = ScalableSprite::create("back.png", [this](){
		Util::director->replaceScene(TransitionFade::create(0.5f, LevelsScene::createWithChapter(this->m_nChapter)));
	});
	btnPlay->setPosition(U::cx - 80, 50);
	this->addChild(btnPlay, 1001);

	ScalableSprite *btnReload = ScalableSprite::create("reload.png", [this](){
		this->loadLevel();
		this->scaleBlocks(0);
	});
	btnReload->setPosition(U::cx + 80, 50);
	this->addChild(btnReload);

	int x = U::cx - 2 * 100 - 50 - 2 * 10;
	int y = U::cy - 3 * 100 - 2 * 10 - 5;
	m_playArea.setRect(x, y, 5 * 100 + 4 * 10, 6 * 100 + 5 * 10);
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

	this->loadLevel();

    return true;
}

void GameScene::loadLevel()
{
	if (m_levelIndicator == nullptr)
	{
		auto label = U::labelWithoutTranslate("", 35, 1);
		label->setPosition(U::width - 20, U::height - 30);
		label->setAnchorPoint(Vec2(1, 0.5));
		this->addChild(label, 1001);

		m_levelIndicator = label;
	}

	stringstream s;
	s << U::t("Level") << " " << this->m_nChapter + 1 << " - " << this->m_nLevel + 1;
	m_levelIndicator->setString(s.str());

	if (m_tipLabel)
	{
		m_tipLabel->removeFromParent();
		m_tipLabel = nullptr;
	}

	rapidjson::Value& levelData = U::getLevel(m_nChapter, m_nLevel);
	if (levelData.HasMember("tip"))
	{
		int yj = U::cy + 3 * 100 + 2 * 10 + 5;

		const char* tip = levelData["tip"].GetString();
		auto tipLabel = U::label(tip, 45, 1);
		tipLabel->setHorizontalAlignment(TextHAlignment::CENTER);
		tipLabel->setVerticalAlignment(TextVAlignment::TOP);
		tipLabel->setDimensions(U::width, yj - 30);
		tipLabel->setPosition(U::cx, (yj - 30) / 2);
		this->addChild(tipLabel, 1000);

		this->m_tipLabel = tipLabel;
	}

	for (int i = 0; i < m_blocks.size(); i++)
	{
		Block *block = m_blocks.at(i);
		block->removeFromParentAndCleanup(true);
	}

	m_blocks.clear();

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
					block = DraggableBlock::create(U::getColorOfBlockValue(_v), 
						to_string(_v),
						CC_CALLBACK_3(GameScene::onBlockBegan, this),
						CC_CALLBACK_3(GameScene::onBlockMoved, this),
						CC_CALLBACK_3(GameScene::onBlockEnded, this));
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
				block->setScale(0.9f);
				this->m_blocks.pushBack(block);
			}
		}
	}
}

void GameScene::onEnter()
{
	Scene::onEnter();
	this->scaleBlocks();
}

void GameScene::scaleBlocks(float delay /*= 0.3*/)
{
	for (size_t i = 0; i < m_blocks.size(); i++)
	{
		Block *block = m_blocks.at(i);
		Sequence *s = Sequence::createWithTwoActions(
			DelayTime::create(i * 0.01 + delay),
			EaseBackOut::create(ScaleTo::create(0.2, 1))
			);
		block->runAction(s);
	}
}

void GameScene::onBlockBegan(Ref *sender, Touch *touch, Event *event)
{
	DraggableBlock *block = (DraggableBlock *)sender;
	block->setDropped(false);
}

void GameScene::onBlockMoved(Ref *sender, Touch *touch, Event *event)
{
	Point point = touch->getLocation();
	DraggableBlock *block = (DraggableBlock *)sender;
	Point startPoint = block->getDragStartPoint();

	Point *newPoint = nullptr;
	if (point.x - startPoint.x >= 60)
	{
		newPoint = new Point(startPoint.x + 110, startPoint.y);
	} 
	else if (point.x - startPoint.x <= -60)
	{
		newPoint = new Point(startPoint.x - 110, startPoint.y);
	}
	else if (point.y - startPoint.y >= 60)
	{
		newPoint = new Point(startPoint.x, startPoint.y + 110);
	}
	else if (point.y - startPoint.y <= -60)
	{
		newPoint = new Point(startPoint.x, startPoint.y - 110);
	}

	if (newPoint && m_playArea.containsPoint(*newPoint))
	{
		block->setDropped(true);
		block->moveTo(*newPoint, 0.1f);
	}
}

void GameScene::onBlockEnded(Ref *sender, Touch *touch, Event *event)
{
	DraggableBlock *block = (DraggableBlock *)sender;
	if (!block->isDropped())
	{
		block->revert();
	}
	else 
	{
		Vec2 pos = block->getPosition();
		DraggableBlock *under = nullptr;
		for (size_t i = 0; i < m_blocks.size(); i++)
		{
			DraggableBlock *b = (DraggableBlock *)m_blocks.at(i);
			if (!b->isVisible() || b == block)
			{
				continue;
			}
			Vec2 p = b->getPosition();
			if (pos.distanceSquared(p) < 1)
			{
				under = b;
				break;
			}
		}
		if (under == nullptr)
		{
			block->decrease();
		}
		else
		{
			under->setVisible(false);
			int underValue = under->getValue();
			int oldValue = block->getValue();
			if (underValue == oldValue - 1)
			{
				block->updateValue(oldValue + 1);
			}
		}
		this->checkIfDone();
	}
}

void GameScene::checkIfDone()
{
	int visibleCount = 0;
	for (size_t i = 0; i < m_blocks.size(); i++)
	{
		DraggableBlock *b = (DraggableBlock *)m_blocks.at(i);
		if (b->isVisible())
		{
			visibleCount++;
		}
	}
	if (visibleCount == 1)
	{
		this->showDoneLayer();
	}
}

void GameScene::showDoneLayer()
{
	ScalableSprite *btnMenu = ScalableSprite::create("menu.png", [this](){
		Util::director->replaceScene(TransitionFade::create(0.5f, LevelsScene::createWithChapter(this->m_nChapter)));
	});

	ScalableSprite *btnNext = ScalableSprite::create("next.png", [this](){
		m_doneLayer->removeFromParent();
		m_doneLayer = nullptr;
		// TODO: add the level and chapter
		this->m_nLevel++;
		this->loadLevel();
		this->scaleBlocks(0);
	});
	m_doneLayer = LevelLayer::create(Color4B(109, 160, 67, 255), btnMenu, btnNext);
	this->addChild(m_doneLayer, 9999);
}

void GameScene::showFailLayer()
{
	ScalableSprite *btnMenu = ScalableSprite::create("menu.png", [this](){
		Util::director->replaceScene(TransitionFade::create(0.5f, LevelsScene::createWithChapter(this->m_nChapter)));
	});

	ScalableSprite *btnReload = ScalableSprite::create("replay.png", [this](){
		m_failLayer->removeFromParent();
		m_failLayer = nullptr;
		this->loadLevel();
	});
	m_failLayer = LevelLayer::create(Color4B(87, 23, 24, 255), btnMenu, btnReload);
	this->addChild(m_failLayer, 9999);
}
