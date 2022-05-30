#include "RightHand.h"

RightHand::RightHand()
{

	m_Model.Load("Data/CatsModel/Righthand.gltf");

	m_StartMat = m_Mat;

	Math::Matrix Rot;

	Rot = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(-105));

	m_EndMat = Rot * m_Mat;

	m_AnimeFrame = 0;

}

RightHand::~RightHand()
{

	m_Model.Release();

}

void RightHand::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_MasterMat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

void RightHand::AnimateProc()
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

const Math::Matrix& RightHand::GetMat()const
{
	return m_Mat;
}

Math::Matrix& RightHand::GetMasterMat()
{
	return m_MasterMat;
}

void RightHand::SetAnimateFrame(const float _val)
{
	m_AnimeFrame += _val;
	if(m_AnimeFrame > 1)
	{
		m_AnimeFrame = 1;
	}
	if (m_AnimeFrame < 0)
	{
		m_AnimeFrame = 0;
	}
}

const float& RightHand::GetAnimateFrame()const
{
	return m_AnimeFrame;
}


