#include "Util.h"
#include "json/rapidjson.h"
#include "json/document.h"

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
unordered_map<string, string>* Util::lang;
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
	
	Util::lang = new unordered_map<string, string>;
	string str = FileUtils::getInstance()->getStringFromFile("i18n/zh-CN.json");
	CCLOG("%s\n", str);

	rapidjson::Document d;
	d.Parse<0>(str.c_str());
	if (d.HasParseError())
	{
		CCLOG("GetParseError %s\n", d.GetParseError());
	}
	if (d.IsObject()) 
	{
		for (rapidjson::Value::ConstMemberIterator itr = d.MemberonBegin();
			itr != d.MemberonEnd(); ++itr)
		{
			Util::lang->emplace(itr->name.GetString(), itr->value.GetString());
		}
	}

	Util::fonts.push_back("fonts/calibrib.ttf");
	Util::fonts.push_back("fonts/HOPE.ttf");

	Util::isEffectEnabled = Util::userDefault->getBoolForKey(kConfigEffect, true);
	
	Util::spriteFrameCache->addSpriteFramesWithFile("image/common.plist");

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
	if (Util::lang)
	{
		unordered_map<string, string>::const_iterator it = Util::lang->find(key);
		if (it != Util::lang->end())
		{
			return it->second;
		}
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
	vector<string> paths = FileUtils::getInstance()->getSearchPaths();
	auto label = Label::createWithTTF(U::t(text), Util::fonts.at(fontIndex), fontSize);
	return label;
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
