#include "Headers.h"

Stairs::Stairs(Math::Vector3 _startVec, Math::Vector3 _endVec)
{

	m_Model.Load("Data/GroundAll/Stairs/Stairs.gltf");

	m_Mat = DirectX::XMMatrixTranslation(_startVec.x, _startVec.y, _startVec.z);

	m_StartPos = Math::Vector3(_startVec.x, _startVec.y, _startVec.z);

	m_EndPos = Math::Vector3(_endVec.x, _endVec.y, _endVec.z);

	m_Pos = m_StartPos;

	m_WaitTime = 0;

	m_SinAngle = 0;

	m_Flag=true;

	m_MoveScale = Math::Vector3(0,0,0);

	m_Speed = 0.5f;

	m_AccelFlag = true;//Accel on

	m_FirstTimeChangeFlag = false;

	m_SoundStairMove = SOUNDMANAGER.AddSoundEffect("Data/Sound/StairsMove.wav");

}

Stairs::~Stairs()
{

	m_Model.Release();

}
void Stairs::Update()
{
	m_Mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);

	Math::Vector3 directVec = m_EndPos - m_Mat.Translation();

	float len;//Goal distance

	len = directVec.Length();


	if (m_FirstTimeChangeFlag == false)
	{
		m_FirstTimeChangeFlag = true;
		if(m_StartPos.x>0)
		{
			m_StartPos.x -= 20;
		}else

		{
			m_StartPos.x += 20; 
		}
		m_SoundStairMove->InstancePlay();
	}

	if (len < m_Speed || (len <= 0.2f))//Goul Arrived
	{

		m_Pos = m_EndPos;

		m_Speed = 0;

		Math::Vector3 tmpVec;

		//Change startpos and endpos

		tmpVec = m_StartPos;

		m_StartPos = m_EndPos;

		m_EndPos = tmpVec;

	}
	else
	{
		if (len < 50)
		{
			if (m_AccelFlag == true)
			{
				m_AccelFlag = false;

				m_SlowRate = m_Speed / len; //
			}
			m_Speed = len * m_SlowRate;
		}
		else
		{
			m_Speed += 0.005f;
		}

		directVec.Normalize();

		m_MoveScale = m_Speed * directVec;

		m_Pos += m_Speed * directVec;

	}

}

void Stairs::Draw()
{

		SHADER.m_standardShader.SetWorldMatrix(m_Mat);

		SHADER.m_standardShader.DrawModel(&m_Model);

}

const KdModel& Stairs::GetModel()const
{

	return m_Model;

}
const Math::Matrix& Stairs::GetMat()const
{

	return m_Mat;

}

const bool& Stairs::GetFlag() const
{

	return m_Flag;

}

const Math::Vector3& Stairs::GetMoveScale()const
{

	return m_MoveScale;

}


void Stairs::SetFlag(const bool _flag)
{

	m_Flag = _flag;

}


