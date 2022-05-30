#include "Headers.h"

SoundManager::~SoundManager()
{

	AllDelete();

}

SoundBgm* SoundManager::AddSoundBgm(std::string _fileName)
{

	SoundBgm* newOne;

	newOne = new SoundBgm(_fileName);

	m_SoundCollection.push_back(newOne);

	return newOne;

}

SoundEffect* SoundManager::AddSoundEffect(std::string _fileName)
{

	SoundEffect* newOne;

	newOne = new SoundEffect(_fileName);

	m_SoundCollection.push_back(newOne);

	return newOne;

}

void SoundManager::Update()
{

	for (UINT i = 0; i < m_SoundCollection.size(); i++)
	{
		m_SoundCollection[i]->Update();

		if (m_SoundCollection[i]->SoundInstanceIsPlay() == false)
		{


			delete m_SoundCollection[i];

			m_SoundCollection.erase(m_SoundCollection.begin() + i);

			i--;

		}

	}

}

void SoundManager::AllDelete()
{

	for (UINT i = 0; i < m_SoundCollection.size(); i++)
	{

		delete m_SoundCollection[i];

	}

	m_SoundCollection.clear();

}

