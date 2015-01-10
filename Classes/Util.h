#pragma once

#include "Global.h"
#include "CrossHelper.h"

class Util
{
public:
	static Director *director;
	static cocos2d::Size size;
	static cocos2d::Point origin;
	static cocos2d::Point center;
	static SpriteFrameCache *spriteFrameCache;
	static SimpleAudioEngine *audioEngine;
	static UserDefault *userDefault;
	static FileUtils *fileUtils;
	static ValueMap lang;
	static vector<string> fonts;
	static string configFilePath;
	static Document data;
	static CrossHelper *crossHelper;
	static bool isEffectEnabled;

	static float width;
	static float height;
	static float cx;
	static float cy;

public:
	static void init();

	static string t(string key);
	static cocos2d::Size p(float x, float y);

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

	static ValueMap getConfig();

	static void addSkippedLevel(int chapter, int level);
	static void removeFromSkippedLevel(int chapter, int level);
	static bool isLevelSkipped(int chapter, int level);
	static ValueVector getAllSkippedLevels();
    
    static bool checkPlayCount();
    
private:
    static int playCount;
};

typedef Util U;

