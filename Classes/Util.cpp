#include "Util.h"

Director* Util::director;
cocos2d::Size Util::size = cocos2d::Size(0, 0);
float Util::width;
float Util::height;
float Util::cx;
float Util::cy;
cocos2d::Point Util::origin = cocos2d::Point(0, 0);
cocos2d::Point Util::center = cocos2d::Point(0, 0);
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
	Util::center = cocos2d::Point(cx, cy);

	vector<string> paths;
	paths.push_back("fonts");
	paths.push_back("i18n");
	paths.push_back("sound");
	paths.push_back("image");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	Util::lang = FileUtils::getInstance()->getValueMapFromFile("i18n/zh-CN.plist");

	Util::fonts.push_back("fonts/calibrib.ttf");
	Util::fonts.push_back("fonts/FZMM.TTF");

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
	key = Util::replace(key, "\n", "\\n");
	ValueMap::const_iterator it = Util::lang.find(key);
	if (it != Util::lang.end())
	{
		key = it->second.asString();
	}
	key = Util::replace(key, "\\n", "\n");
	return key;
}

cocos2d::Size Util::p( float x, float y )
{
	cocos2d::Point o = Util::origin;
	return cocos2d::Size(o.x + x, o.y + y);
}

Label *Util::label(const char *text, float fontSize, int fontIndex)
{
	return Util::labelWithoutTranslate(U::t(text), fontSize, fontIndex);
}

Label * Util::labelWithoutTranslate(const string& text, float fontSize /*= 35*/, int fontIndex /*= 0*/)
{
	return Label::createWithTTF(text, Util::fonts.at(fontIndex), fontSize);
}

void Util::playEffect(const char *effect /*= "sound/effect.mp3"*/)
{
	if (Util::isEffectEnabled)
	{
		Util::audioEngine->playEffect(effect);
	}
}

void Util::toggleEffect(const bool enabled)
{
	Util::userDefault->setBoolForKey(kConfigEffect, enabled);
	Util::isEffectEnabled = enabled;
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

rapidjson::Value & Util::getLevel(int chapter, int level)
{
	int count = Util::getLevelCount(chapter);
	assert(level >= 0 && level < count);

	rapidjson::Value& chapterData = Util::getChapter(chapter);
	return chapterData["levels"][level];
}

std::string Util::replace(const string& str, const string& src, const string& dest)
{
	string ret(str);
	string::size_type pos = ret.find(src);
	while (pos != string::npos)
	{
		ret = ret.replace(pos, src.length(), dest);
		pos = ret.find(src, pos + dest.length());
	}
	return ret;
}

cocos2d::Color4B Util::getColorOfBlockValue(int v)
{
	static Color4B colors[] = {
		Color4B::BLACK,					/* 0 */
		Color4B(222, 168, 64, 255),
		Color4B(68, 114, 148, 255),
		Color4B(255, 85, 85, 255),
		Color4B(153, 136, 154, 255),
		Color4B(187, 52, 85, 255),		/* 5 */
		Color4B(66, 153, 220, 255),
		Color4B(221, 152, 119, 255),
		Color4B(135, 102, 85, 255),
		Color4B(203, 153, 204, 255),
		Color4B(67, 85, 85, 255),		/* 10 */
		Color4B(170, 204, 205, 255),
		Color4B(255, 220, 152, 255),
		Color4B(245, 66, 150, 255),
		Color4B(68, 114, 148, 255),
		Color4B(187, 52, 85, 255),		/* 15 */
		Color4B::BLACK
	};
	if (v >= 0 && v <= 16)
	{
		return colors[v];
	}
	return Color4B::BLACK;
}
