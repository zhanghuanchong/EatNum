#pragma once

#include "CrossHelper.h"

class CrossAndroid : public CrossHelper
{
public:
    virtual void showInterstitialAd();
    virtual void sendMail();
    virtual void askForExit();

    virtual ~CrossAndroid();
};


