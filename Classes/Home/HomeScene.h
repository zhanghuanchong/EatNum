#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "Util.h"

class HomeScene : public Scene
{
public:
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);
};

#endif // __HOME_SCENE_H__
