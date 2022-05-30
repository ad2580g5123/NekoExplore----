#include "Headers.h"

SoundEffect::SoundEffect(std::string _fileName)
{

	m_Sound->Load(_fileName);

	m_SoundInstance = m_Sound->CreateInstance(false);

}

void SoundEffect::Update()
{
	
}

void SoundEffect::InstancePlay()
{
	m_SoundInstance->Play();

	m_SoundInstance->SetVolume(0.05);
}


void SoundEffect::RePlay()
{
	m_SoundInstance->Resume();

	m_SoundInstance->SetVolume(0.1);
}

void SoundEffect::SetVol(float _vol)
{
	m_SoundInstance->SetVolume(_vol);
}
