#include "CrossAndroid.h"
#include "Util.h"

#include <jni.h>
#include "../cocos2d/cocos/platform/android/jni/JniHelper.h"
#include <android/log.h>

#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

CrossAndroid::~CrossAndroid()
{}

void CrossAndroid::commentInAppStore()
{

}

void CrossAndroid::showGameCenter()
{

}

void CrossAndroid::showActivities()
{
}

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

void CrossAndroid::reportScore(int score)
{

}

void CrossAndroid::sendMail()
{

}
