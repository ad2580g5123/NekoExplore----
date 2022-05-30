#pragma once

class SoundEffect :public Sound
{
public:

	SoundEffect(std::string _fileName);

	void Update()override;

	void InstancePlay();

	void RePlay();

	void SoundEffect::SetVol(float _vol);
private:
};