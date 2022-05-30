#include "Headers.h"
PushCrystal::PushCrystal(GameScene* _gamescene)
{

	m_GameScene = _gamescene;

	m_Model.Load("Data/GroundAll/Crystal/PushCrystal.gltf");

	//m_mat = DirectX::XMMatrixTranslation(0, 0, 0);

	m_Flag = true;

	m_Alpha = 1.0f;

	m_Hp = 30;

	m_Radius = 5;

	m_Mat = DirectX::XMMatrixTranslation(110, 3.5, 262);

	m_SoundFlag = true;

	m_Sound = SOUNDMANAGER.AddSoundEffect("Data/Sound/PushCrystalSound.wav");

	m_AccelAngle = 0;

}

PushCrystal::~PushCrystal()
{

	m_Model.Release();

}

void PushCrystal::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

void PushCrystal::Update()
{


	m_Sound->SetVol(0.5f);

	Ground& ground = m_GameScene->GetGround();

	PlayerGameScene& player = m_GameScene->GetPlayer();


	Math::Vector3 targetVec = m_Mat.Translation() - player.GetPos();

	float dis = targetVec.Length();

	if (dis < GetRadius() + player.GetRadius())
	{

		if ((m_Mat.Translation().x > 130 && m_Mat.Translation().x < 136) && (m_Mat.Translation().z > 374 && m_Mat.Translation().z < 378))
		{


			m_Mat._42+=-0.25;

			player.SetPos(player.GetPos() + player.GetMoveVec() *-1);

			if (m_Mat._42 <= 0)
			{

				m_Mat._42 = 0;

			}

		}
		else
		{

			if (m_SoundFlag == true)
			{

				m_Sound->InstancePlay();

				m_SoundFlag = false;

			}

			if (m_Sound->SoundInstanceIsPlay() == false)
			{
				m_Sound->InstancePlay();
			}

			Math::Vector3 cross = DirectX::XMVector3Cross(player.GetMoveVec(), Math::Vector3(0, 1, 0));

			Math::Matrix matInverce = m_Mat.Invert();

			Math::Vector3 localVec = DirectX::XMVector3TransformNormal(cross, matInverce);

			float angle = (player.GetMovePower() / (m_Radius * 2 * 3.14)) * 360;

			Math::Matrix rot = DirectX::XMMatrixRotationAxis(localVec, DirectX::XMConvertToRadians(-m_AccelAngle));

			if(m_AccelAngle< angle)
			{
				m_AccelAngle += 0.05f;
			}else
			{
				m_AccelAngle = angle;
			}
			

			m_Mat = rot * m_Mat;

			AddPos(player.GetMoveVec() * 0.5);

			player.SetPos(player.GetPos() + player.GetMoveVec() * -0.5);
		}

	}

}

const Math::Matrix& PushCrystal::GetMat() const
{

	return m_Mat;

}

const KdModel& PushCrystal::GetModel() const
{

	return m_Model;

}

const Math::Vector3& PushCrystal::GetPos() const
{
	return m_Mat.Translation();
}

const bool& PushCrystal::GetFlag() const
{

	return m_Flag;

}

const float& PushCrystal::GetHp() const
{

	return m_Hp;

}

const float& PushCrystal::GetAlpha() const
{

	return m_Alpha;

}

const float& PushCrystal::GetRadius() const
{

	return m_Radius;

}

void PushCrystal::SetFlag(const bool _flag)
{

	m_Flag = _flag;

}

void PushCrystal::SetHp(const float _hp)
{

	m_Hp += _hp;

}

void PushCrystal::SetAlpha(const float _alpha)
{

	m_Alpha += _alpha;

	if (m_Alpha <= 0)
	{

		m_Alpha = 0;

	}

}

void PushCrystal::AddPos(const Math::Vector3 _vec)
{

	m_Mat._41 += _vec.x;
	m_Mat._42 += _vec.y;
	m_Mat._43 += _vec.z;
}
