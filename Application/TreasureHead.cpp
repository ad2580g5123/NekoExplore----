#include "Headers.h"

TreasureHead::TreasureHead()
{

	m_Model.Load("Data/GroundAll/Treasure/TreasureBoxHead.gltf");

	//m_Mat = DirectX::XMMatrixTranslation(-679, -122, 451);

	m_StartMat = m_Mat;

	Math::Matrix RotZ;

	RotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(90));

	m_EndMat = RotZ *m_Mat;

	m_AnimeFrame = 0; 

}

TreasureHead::~TreasureHead()
{
	m_Model.Release();
}

void TreasureHead::Update()
{

	Math::Matrix Posmat;

	Posmat = DirectX::XMMatrixTranslation(-679, -122, 451);

	m_MasterMat = m_Mat* Posmat;

	

}

void TreasureHead::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_MasterMat);

	SHADER.m_standardShader.DrawModel(&m_Model);
}

void TreasureHead::AnimateProc()
{

	Math::Quaternion startQua;

	Math::Quaternion endQua;

	Math::Quaternion nowQua;

	startQua = DirectX::XMQuaternionRotationMatrix(m_StartMat);

	endQua = DirectX::XMQuaternionRotationMatrix(m_EndMat);

	nowQua = DirectX::XMQuaternionSlerp(startQua, endQua, m_AnimeFrame);

	m_Mat = DirectX::XMMatrixRotationQuaternion(nowQua);


}

void TreasureHead::SetAnimateFrame(const float _val)
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

const float& TreasureHead::GetAnimateFrame()const
{

	return m_AnimeFrame;

}