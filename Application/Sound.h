#pragma once

class Sound
{
public:
	Sound();

	virtual ~Sound();

	virtual void Update();

	bool SoundInstanceIsPlay();

private:

protected:

	std::shared_ptr<KdSoundEffect>m_Sound;

	std::shared_ptr<KdSoundInstance> m_SoundInstance;

};