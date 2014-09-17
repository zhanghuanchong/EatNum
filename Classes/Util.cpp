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
Dictionary* Util::lang;
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
	
	Util::lang = Dictionary::createWithContentsOfFile("i18n/zh-CN.xml");
	Util::lang->retain();

	Util::fonts.push_back("fonts/calibrib.ttf");
	Util::fonts.push_back("fonts/HOPE.ttf");

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