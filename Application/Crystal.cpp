#include "Headers.h"
Crystal::Crystal(const Math::Vector3 _pos,const int _hp)
{

	m_Model.Load("Data/GroundAll/Crystal/Crystal.gltf");

	m_Mat = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z); //-48.5, 22.25, -56.25

	//m_mat = DirectX::XMMatrixTranslation(0, 0, 0);

	m_Flag = true;

	m_Alpha = 1.0f;

	m_Hp = _hp;

	m_Radius = 5;

	m_CheckFlag = false;

	m_Sound = SOUNDMANAGER.AddSoundEffect("Data/Sound/CrystalSound.wav");

}

Crystal::~Crystal()
{

	m_Model.Release();

}

void Crystal::Draw()
{
	if (m_Flag == true)
	{

		SHADER.m_standardShader.SetWorldMatrix(m_Mat);

		SHADER.m_standardShader.DrawModel(&m_Model,m_Alpha);
	}
}

void Crystal::Update()
{
	if (m_Flag == true)
	{

		m_Pos = m_Mat.Translation();

		if (m_Hp <= 10 && m_CheckFlag==false)
		{
			m_Model.Release();
			m_Model.Load("Data/GroundAll/Crystal/Crystal2.gltf");
			m_CheckFlag = true;
		}
		if (m_Hp <= 0)
		{

			SetAlpha(-0.02);

			if (GetAlpha() <= 0)
			{

				SetFlag(false);

			}
		}
	}
}

const Math::Matrix& Crystal::GetMat() const
{

	return m_Mat;

}

const KdModel& Crystal::GetModel() const
{

	return m_Model;

}

const Math::Vector3& Crystal::GetPos() const
{

	return m_Pos;

}

const bool& Crystal::GetFlag() const
{

	return m_Flag;

}

const float& Crystal::GetHp() const
{

	return m_Hp;

}

const float& Crystal::GetAlpha() const
{

	return m_Alpha;

}

const float& Crystal::GetRadius() const
{

	return m_Radius;

}

void Crystal::SetFlag(const bool _flag)
{

	m_Flag = _flag;

}

void Crystal::SetHp(const float _hp)
{

	m_Hp += _hp;

}

void Crystal::SetAlpha(const float _alpha)
{

	m_Alpha += _alpha;

	if (m_Alpha <= 0)
	{

		m_Alpha = 0;

	}

}

void Crystal::SetPos(const Math::Vector3 _vec)
{

		m_Mat.Translation() = _vec;

}

void Crystal::SoundPlay()
{
	m_Sound->InstancePlay();
}
