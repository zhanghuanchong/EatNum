#include "TemplateLayer.h"

bool TemplateLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    return true;
}

void TemplateLayer::onEnterTransitionDidFinish()
{

}
