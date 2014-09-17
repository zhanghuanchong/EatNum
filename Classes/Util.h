#pragma once

#include "Global.h"

class Util
{
public:
	static Director *director;
	static Size size;
	static Point origin;
	static SpriteFrameCache *spriteFrameCache;
	static SimpleAudioEngine *audioEngine;
	static UserDefault *userDefault;

	static Dictionary *lang;
	static const char *fontName;
	static Size designResolutionSize;
	static bool isEffectEnabled;

public:
	static void init();

	static const char *t(const char *key);
	static Size p(float x, float y);

	static Label *label(const char *text, float fontSize = 35);

	static void playEffect(const char *effect);
};

typedef Util U;

