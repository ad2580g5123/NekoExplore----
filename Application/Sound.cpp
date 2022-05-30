#include "Headers.h"

Sound::Sound()
{

	m_Sound = std::make_shared<KdSoundEffect>();//-->new

}

Sound::~Sound()
{

}

void Sound::Update()
{

}

bool Sound::SoundInstanceIsPlay()
{

	return m_SoundInstance->IsPlay();

}
