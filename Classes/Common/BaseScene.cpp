#include "BaseScene.h"

bool BaseScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	m_sound = ScalableSprite::create("sound.png", [](){

	});
	m_sound->setPosition(U::width - 10, 10);
	m_sound->setAnchorPoint(Vec2(1, 0));
	this->addChild(m_sound, 1000);

	m_music = ScalableSprite::create("music.png", [](){

	});
	m_music->setPosition(U::width - 78, 10);
	m_music->setAnchorPoint(Vec2(1, 0));
	this->addChild(m_music, 1000);

    return true;
}
