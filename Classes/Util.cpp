#include "Util.h"

Director* Util::director;
Size Util::size = Size(0, 0);
Point Util::origin = Point(0, 0);
SpriteFrameCache* Util::spriteFrameCache;
SimpleAudioEngine* Util::audioEngine;
UserDefault *Util::userDefault;
Dictionary* Util::lang;
const char * Util::fontName;
Size Util::designResolutionSize = Size(640, 960);
bool Util::isEffectEnabled = true;

void Util::init()
{
	Util::director = Director::getInstance();
	Util::spriteFrameCache = SpriteFrameCache::getInstance();
	Util::audioEngine = SimpleAudioEngine::getInstance();
	Util::userDefault = UserDefault::getInstance();

	Util::size = Util::director->getVisibleSize();
	Util::origin = Util::director->getVisibleOrigin();
	
	Util::lang = Dictionary::createWithContentsOfFile("i18n/zh-CN.xml");
	Util::lang->retain();

	Util::fontName = "fonts/calibrib.ttf"; // "fonts/HOPE.ttf";

	Util::isEffectEnabled = Util::userDefault->getBoolForKey(kConfigEffect, true);
}

const char * Util::t( const char *key )
{
	if (Util::lang)
	{
		String *c = (String *)Util::lang->objectForKey(key);
		if (c)
		{
			return c->getCString();
		}
	}
	return key;
}

cocos2d::Size Util::p( float x, float y )
{
	Point o = Util::origin;
	return Size(o.x + x, o.y + y);
}

Label *Util::label(const char *text, float fontSize)
{
	vector<string> paths = FileUtils::getInstance()->getSearchPaths();
	auto label = Label::createWithTTF(U::t(text), Util::fontName, fontSize);
	return label;
}

void Util::playEffect(const char *effect)
{
	if (Util::isEffectEnabled)
	{
		Util::audioEngine->playEffect(effect);
	}
}