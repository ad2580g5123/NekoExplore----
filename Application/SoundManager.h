#pragma once
class SoundManager
{
public:

	~SoundManager();

	SoundBgm* AddSoundBgm(std::string _fileName);

	SoundEffect* AddSoundEffect(std::string _fileName);//Distance

	void Update();

	void AllDelete();

	static SoundManager& GetInstance()
	{

		static SoundManager instance;

		return instance;

	}

private:

	std::vector<Sound*> m_SoundCollection;

};
#define SOUNDMANAGER SoundManager::GetInstance()