#include "CrossHelper.h"
#include "Util.h"

CrossHelper::~CrossHelper()
{}

void CrossHelper::commentInAppStore()
{
	CCLog("CrossHelper::commentInAppStore");
}

void CrossHelper::showGameCenter()
{
	CCLog("CrossHelper::showGameCenter");
}

void CrossHelper::showActivities()
{
	CCLog("CrossHelper::showActivities");
}

void CrossHelper::showInterstitialAd()
{
	CCLog("CrossHelper::showInterstitialAd");
}

void CrossHelper::reportScore(int score)
{
	CCLog("CrossHelper::reportScore: %i", score);
}

void CrossHelper::sendMail()
{
	CCLog("CrossHelper::sendMail");
}

void CrossHelper::askForExit()
{
	CCLog("CrossHelper::askForExit");
}
