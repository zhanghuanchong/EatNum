#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "Util.h"

class SplashScene : public Scene
{
private:
	Sprite *m_pLogo;
	Label *m_pMotto;

public:
    virtual bool init();
	virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif // __SPLASH_SCENE_H__
