#pragma once

#include "CrossHelper.h"

class CrossAndroid : public CrossHelper
{
public:
    virtual void commentInAppStore();
    virtual void showGameCenter();
    virtual void showActivities();
    virtual void showInterstitialAd();
    virtual void reportScore(int score);
    virtual void sendMail();

    virtual ~CrossAndroid();
};


