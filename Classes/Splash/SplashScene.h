#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "Util.h"

class SplashScene : public Scene
{
public:
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif // __SPLASH_SCENE_H__
