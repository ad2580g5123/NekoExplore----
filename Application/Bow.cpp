#include "Bow.h"

Bow::Bow()
{

	m_Model.Load("Data/CatsModel/Bow.gltf");

	m_StartMat = m_Mat;

	Math::Matrix Rot;

	Rot = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(-105));

	Math::Matrix Rot2;

	Rot2 = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-150));

	m_EndMat = Rot * Rot2 * m_Mat;

	m_AnimeFrame = 0;

}

Bow::~Bow()
{

	m_Model.Release();

}

void Bow::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_MasterMat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

void Bow::AnimateProc()
{

	Math::Quaternion startQua;

	Math::Quaternion endQua;

	Math::Quaternion nowQua;

	startQua = DirectX::XMQuaternionRotationMatrix(m_StartMat);

	endQua = DirectX::XMQuaternionRotationMatrix(m_EndMat);

	nowQua = DirectX::XMQuaternionSlerp(startQua, endQua, m_AnimeFrame);

	m_Mat = DirectX::XMMatrixRotationQuaternion(nowQua);

	//Math::Vector3 startPos;
	//Math::Vector3 endPos;
	//Math::Vector3 nowPos;
	//startPos = m_startMat.Translation();
	//endPos = m_endMat.Translation();
	//nowPos = DirectX::XMVectorLerp(startPos, endPos, m_animeFrame);
	////	m_mat_righthand.Translation(nowPos);
}

const Math::Matrix& Bow::GetMat()const
{

	return m_Mat;

}

Math::Matrix& Bow::GetMasterMat()
{

	return m_MasterMat;

}

void Bow::SetAnimateFrame(const float _val)
{

	m_AnimeFrame += _val;

	if (m_AnimeFrame > 1)
	{

		m_AnimeFrame = 1;

	}

	if (m_AnimeFrame < 0)
	{

		m_AnimeFrame = 0;

	}

}

const float& Bow::GetAnimateFrame()const
{

	return m_AnimeFrame;

}


