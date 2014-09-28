#include "Util.h"

Director* Util::director;
Size Util::size = Size(0, 0);
float Util::width;
float Util::height;
float Util::cx;
float Util::cy;
Point Util::origin = Point(0, 0);
Point Util::center = Point(0, 0);
SpriteFrameCache* Util::spriteFrameCache;
SimpleAudioEngine* Util::audioEngine;
UserDefault *Util::userDefault;
ValueMap Util::lang;
Document Util::data;
vector<string> Util::fonts;
bool Util::isEffectEnabled = true;

void Util::init()
{
	Util::director = Director::getInstance();
	Util::spriteFrameCache = SpriteFrameCache::getInstance();
	Util::audioEngine = SimpleAudioEngine::getInstance();
	Util::userDefault = UserDefault::getInstance();

	Util::size = Util::director->getVisibleSize();
	Util::width = size.width;
	Util::height = size.height;
	Util::origin = Util::director->getVisibleOrigin();
	Util::cx = Util::origin.x + Util::width / 2;
	Util::cy = Util::origin.y + Util::height / 2;
	Util::center = Point(cx, cy);

	vector<string> paths;
	paths.push_back("fonts");
	paths.push_back("i18n");
	paths.push_back("sound");
	paths.push_back("image");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	Util::lang = FileUtils::getInstance()->getValueMapFromFile("i18n/zh-CN.plist");

	Util::fonts.push_back("fonts/calibrib.ttf");
	Util::fonts.push_back("fonts/HOPE.ttf");

	Util::isEffectEnabled = Util::userDefault->getBoolForKey(kConfigEffect, true);
	
	Util::spriteFrameCache->addSpriteFramesWithFile("image/common.plist");

	string str = FileUtils::getInstance()->getStringFromFile("other/data.json");
	data.Parse<0>(str.c_str());
	if (data.HasParseError())
	{
		CCLOG("GetParseError %s\n", data.GetParseError());
	}

	/*Util::audioEngine->preloadBackgroundMusic("sound/bg.mp3");
	const char *effects[] = {
	"on.mp3",
	"off.mp3",
	"click.mp3"
	};
	for (int i = 0; i < 3; i++)
	{
	Util::audioEngine->preloadEffect(effects[i]);
	}*/
}

string Util::t( string key )
{
	ValueMap::const_iterator it = Util::lang.find(key);
	if (it != Util::lang.end())
	{
		return it->second.asString();
	}
	return key;
}

cocos2d::Size Util::p( float x, float y )
{
	Point o = Util::origin;
	return Size(o.x + x, o.y + y);
}

Label *Util::label(const char *text, float fontSize, int fontIndex)
{
	return Util::labelWithoutTranslate(U::t(text), fontSize, fontIndex);
}

Label * Util::labelWithoutTranslate(const string& text, float fontSize /*= 35*/, int fontIndex /*= 0*/)
{
	return Label::createWithTTF(text, Util::fonts.at(fontIndex), fontSize);
}

void Util::playEffect(const char *effect)
{
	if (Util::isEffectEnabled)
	{
		Util::audioEngine->playEffect(effect);
	}
}

void Util::playBackgroundMusic(const char *file)
{
	if (Util::userDefault->getBoolForKey(kConfigMusic, true))
	{
		Util::audioEngine->playBackgroundMusic(file);
	}
}

int Util::getChapterCount()
{
	return Util::data.Size();
}

rapidjson::Value &Util::getChapter(int i)
{
	int count = Util::getChapterCount();
	if (i >= 0 && i < count)
	{
		return Util::data[i];
	}
	static rapidjson::Value NullValue;
	return NullValue;
}

int Util::getLevelCount(int i)
{
	int count = Util::getChapterCount();
	if (i >= 0 && i < count)
	{
		return Util::data[i]["levels"].Size();
	}
	return 0;
}
