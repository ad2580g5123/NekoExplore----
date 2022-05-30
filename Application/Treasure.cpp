#include "Headers.h"

Treasure::Treasure(GameScene* _gamescene)
{

	if(m_TreasureBody == nullptr)
	{

		m_TreasureBody = new TreasureBody(_gamescene);

	}

	if (m_TreasureHead == nullptr)
	{

		m_TreasureHead = new TreasureHead();

	}
	m_AnimateWaitTime = 0;

	m_Sound = SOUNDMANAGER.AddSoundEffect("Data/Sound/TreasureBoxSound.wav");

	m_SoundFlag = true;
}

Treasure::~Treasure()
{
	if (m_TreasureBody != nullptr)
	{

		delete m_TreasureBody;

		m_TreasureBody = nullptr;

	}

	if (m_TreasureHead != nullptr)
	{

		delete m_TreasureHead;

		m_TreasureHead = nullptr;

	}
	
}

void Treasure::Update()
{

	m_Sound->SetVol(0.8f);

	if (m_TreasureBody != nullptr)
	{

		m_TreasureBody->Update();

	}

	if (m_TreasureHead != nullptr )
	{

		m_TreasureHead->Update();

	}

	if(m_TreasureBody->GetAnimateFlag()==true)
	{
		if (m_SoundFlag == true)
		{

			m_Sound->InstancePlay();

			m_SoundFlag = false;

		}
		
		m_TreasureHead->SetAnimateFrame(0.02f);

		m_TreasureHead->AnimateProc();

		m_AnimateWaitTime++;
	}

}

void Treasure::Draw()
{

	if (m_TreasureBody != nullptr)
	{

		m_TreasureBody->Draw();

	}

	if (m_TreasureHead != nullptr)
	{

		m_TreasureHead->Draw();

	}

}

float Treasure::GetRadius()
{
	return m_TreasureBody->GetRadius();
}

Math::Vector3 Treasure::GetPos()
{
	return m_TreasureBody->GetPos();
}

float Treasure::GetAnimateWaitTime()
{
	return m_AnimateWaitTime;
}
