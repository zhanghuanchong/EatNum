#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "Util.h"

class HomeScene : public Scene
{
public:
    virtual bool init();
	virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);

private:
	Label *labelNom;
	Label *labelNum;

	void menuItemPlayCallback(Ref *pSender);
};

#endif // __HOME_SCENE_H__
