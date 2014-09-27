#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
using namespace std;
using namespace rapidjson;

static const char *kConfigMusic = "Music";
static const char *kConfigEffect = "Effect";

static const Color3B ccBrown = {79, 57, 30};