#include "BaseScene.h"

bool BaseScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	m_sound = ScalableSprite::create("sound.png", [this](){
		bool sound = U::userDefault->getBoolForKey(kConfigEffect, true);
		sound = !sound;
		U::toggleEffect(sound);
		if (sound)
		{
			U::playEffect();
			m_sound->setOpacity(255);
		}
		else
		{
			U::audioEngine->stopAllEffects();
			m_sound->setOpacity(100);
		}
	});
	m_sound->setPosition(U::width - 10, 10);
	m_sound->setAnchorPoint(Vec2(1, 0));
	bool sound = U::userDefault->getBoolForKey(kConfigEffect, true);
	if (!sound)
	{
		m_sound->setOpacity(100);
	}
	this->addChild(m_sound, 1000);

	m_music = ScalableSprite::create("music.png", [this](){
		bool music = U::userDefault->getBoolForKey(kConfigMusic, true);
		music = !music;
		U::userDefault->setBoolForKey(kConfigMusic, music);
		if (music)
		{
			U::playBackgroundMusic();
			m_music->setOpacity(255);
		}
		else
		{
			U::audioEngine->stopBackgroundMusic();
			m_music->setOpacity(100);
		}
	});
	m_music->setPosition(U::width - 78, 10);
	m_music->setAnchorPoint(Vec2(1, 0));
	bool music = U::userDefault->getBoolForKey(kConfigMusic, true);
	if (!music)
	{
		m_music->setOpacity(100);
	}
	else
	{
		U::playBackgroundMusic();
	}
	this->addChild(m_music, 1000);

    return true;
}
