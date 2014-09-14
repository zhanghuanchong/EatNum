#include "SettingLayer.h"

bool SettingLayer::init()
{
	bool bRet = CCLayer::init();
	if (bRet)
	{
		CCLabelTTF *label = Util::createLabelTTF(kConfigMusic);
		this->addChild(label);
		label->setPosition(ccp(-100, 0));
		label->setColor(ccBrown);

		m_pSwitchMusic = WoodSwitch::create(this, cccontrol_selector(SettingLayer::valueChanged));
		this->addChild(m_pSwitchMusic);
		m_pSwitchMusic->setPosition(ccp(45, 0));
		m_pSwitchMusic->setOn(Util::userDefault->getBoolForKey(kConfigMusic, true));

		label = Util::createLabelTTF(kConfigEffect);
		this->addChild(label);
		label->setPosition(ccp(-100, -100));
		label->setColor(ccBrown);

		m_pSwitchEffect = WoodSwitch::create(this, cccontrol_selector(SettingLayer::valueChanged));
		this->addChild(m_pSwitchEffect);
		m_pSwitchEffect->setPosition(ccp(45, -100));
		m_pSwitchEffect->setOn(Util::userDefault->getBoolForKey(kConfigEffect, true));
	}
	return bRet;
}


void SettingLayer::valueChanged(CCObject* sender, CCControlEvent controlEvent)
{
	if (sender == m_pSwitchMusic)
	{
		Util::userDefault->setBoolForKey(kConfigMusic, m_pSwitchMusic->isOn());
		if (m_pSwitchMusic->isOn())
		{
			Util::audioEngine->playBackgroundMusic(kFileBgMusic);
		}
		else
		{
			Util::audioEngine->stopBackgroundMusic();
		}
	}
	else if (sender == m_pSwitchEffect)
	{
		Util::userDefault->setBoolForKey(kConfigEffect, m_pSwitchEffect->isOn());
		Util::isEffectEnabled = Util::userDefault->getBoolForKey(kConfigEffect, true);
		if (!m_pSwitchEffect->isOn())
		{
			Util::audioEngine->stopAllEffects();
		}
	}
}