#include "Headers.h"

SoundBgm::SoundBgm(std::string _fileName)
{

	m_Sound->Load(_fileName);

	m_SoundInstance = m_Sound->CreateInstance(false);

}

void SoundBgm::Update()
{

	if(m_SoundInstance->IsPlay()==false)
	{

		m_SoundInstance->Play();

		m_SoundInstance->SetVolume(0.01);

	}

}

void SoundBgm::SetSoundInstanceStop()
{
	m_SoundInstance->Stop();
}


