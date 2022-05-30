#include "LeftHand.h"

LeftHand::LeftHand()
{

	m_Model.Load("Data/CatsModel/Lefthand.gltf");

	m_StartMat = m_Mat;

	Math::Matrix RotX;

	RotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(-105));

	Math::Matrix RotZ;

	RotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-150));

	m_EndMat = RotX *RotZ* m_Mat;

	m_AnimeFrame = 0;

}

LeftHand::~LeftHand()
{

	m_Model.Release();

}

void LeftHand::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_MasterMat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

void LeftHand::AnimateProc()
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

const Math::Matrix& LeftHand::GetMat()const
{

	return m_Mat;

}

Math::Matrix& LeftHand::GetMasterMat()
{

	return m_MasterMat;

}

void LeftHand::SetAnimateFrame(const float _val)
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

const float& LeftHand::GetAnimateFrame()const
{

	return m_AnimeFrame;

}


