#pragma once

#include "Global.h"

class Util
{
public:
	static Director *director;
	static Size size;
	static Point origin;
	static Point center;
	static SpriteFrameCache *spriteFrameCache;
	static SimpleAudioEngine *audioEngine;
	static UserDefault *userDefault;
	static ValueMap lang;
	static vector<string> fonts;
	static Document data;
	static bool isEffectEnabled;

	static float width;
	static float height;
	static float cx;
	static float cy;

public:
	static void init();

	static string t(string key);
	static Size p(float x, float y);

	static Label *label(const char *text, float fontSize = 35, int fontIndex = 0);
	static Label *labelWithoutTranslate(const string& text, float fontSize = 35, int fontIndex = 0);

	static void playBackgroundMusic(const char *file = "sound/music.mp3");
	static void playEffect(const char *effect = "sound/effect.mp3");
	static void toggleEffect(const bool enabled);

	static int getChapterCount();
	static rapidjson::Value &getChapter(int i);
	static int getLevelCount(int chapter);
	static rapidjson::Value &getLevel(int chapter, int level);

	static string replace(const string& str, const string& src, const string& dest);

	static Color4B getColorOfBlockValue(int v);
};

typedef Util U;

