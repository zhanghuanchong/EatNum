#include "CrossAndroid.h"
#include "Util.h"

#include <jni.h>
#include "../cocos2d/cocos/platform/android/jni/JniHelper.h"
#include <android/log.h>

#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

CrossAndroid::~CrossAndroid()
{}

void CrossAndroid::showInterstitialAd()
{
	JniMethodInfo info;
	bool ret = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showInterstitialAd", "()V");
	if(ret)
	{
		CCLog("Invoke showInterstitialAd");
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
}

void CrossAndroid::sendMail()
{
	JniMethodInfo info;
	bool ret = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "sendMail", "()V");
	if(ret)
	{
		CCLog("Invoke sendMail");
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
}

void CrossAndroid::askForExit()
{
	JniMethodInfo info;
	bool ret = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "askForExit", "()V");
	if(ret)
	{
		CCLog("Invoke askForExit");
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
}

void CrossAndroid::showActivities()
{
	JniMethodInfo info;
	bool ret = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showActivities", "()V");
	if(ret)
	{
		CCLog("Invoke showActivities");
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
}
