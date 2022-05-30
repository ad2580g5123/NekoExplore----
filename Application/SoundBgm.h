#pragma once

class SoundBgm :public Sound
{
public:

	SoundBgm(std::string _fileName);

	void Update()override;

	void SetSoundInstanceStop();

private:
	

};