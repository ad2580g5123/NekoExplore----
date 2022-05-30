#include "LeftFoot.h"

LeftFoot::LeftFoot()
{

	m_Model.Load("Data/CatsModel/foot.gltf");

	m_StartMat = m_Mat;

	Math::Matrix Rot, RotBack;

	Rot = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(-90));

	RotBack = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90));

	m_EndMat = Rot * m_Mat;

	m_EndMatBack = RotBack * m_Mat;

	m_AnimeFrame = 0;

	m_AnimeFrameBack = 0;

	m_AnimateFlag = 0;

}

LeftFoot::~LeftFoot()
{

	m_Model.Release();

}

void LeftFoot::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_MasterMat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

void LeftFoot::AnimateProc()
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

void LeftFoot::AnimateProcback()
{

	Math::Quaternion startQua;

	Math::Quaternion endQua;

	Math::Quaternion nowQua;

	startQua = DirectX::XMQuaternionRotationMatrix(m_StartMat);

	endQua = DirectX::XMQuaternionRotationMatrix(m_EndMatBack);

	nowQua = DirectX::XMQuaternionSlerp(startQua, endQua, m_AnimeFrameBack);

	m_Mat = DirectX::XMMatrixRotationQuaternion(nowQua);

	//Math::Vector3 startPos;
	//Math::Vector3 endPos;
	//Math::Vector3 nowPos;
	//startPos = m_startMat.Translation();
	//endPos = m_endMat.Translation();
	//nowPos = DirectX::XMVectorLerp(startPos, endPos, m_animeFrame);
	////	m_mat_righthand.Translation(nowPos);
}

const Math::Matrix& LeftFoot::GetMat()const
{

	return m_Mat;

}

Math::Matrix& LeftFoot::GetMasterMat()
{

	return m_MasterMat;

}

const float& LeftFoot::GetAnimateFlag()const
{

	return m_AnimateFlag;

}

const float& LeftFoot::GetAnimateFrame()const
{

	return m_AnimeFrame;

}

const float& LeftFoot::GetAnimateFrameback()const
{

	return m_AnimeFrameBack;

}

void LeftFoot::SetAnimateFrame(const float _val)
{

	m_AnimeFrame += _val;

}

void LeftFoot::SetAnimateFrameback(const float _val)
{

	m_AnimeFrameBack += _val;

}

void LeftFoot::SetAnimateFlag(const float _state)
{

	m_AnimateFlag = _state;

}
void LeftFoot::Animate(float _aniframe)
{

	if (GetAnimateFlag() == 0)
	{

		SetAnimateFrame(_aniframe);

		AnimateProc();

		if (GetAnimateFrame() >= 1)
		{

			SetAnimateFlag(1);

		}

	}

	if (GetAnimateFlag() == 1)
	{

		SetAnimateFrame(-_aniframe);

		AnimateProc();

		if (GetAnimateFrame() < 0)
		{

			SetAnimateFlag(2);

		}
	}

	if (GetAnimateFlag() == 2)
	{

		SetAnimateFrameback(_aniframe);

		AnimateProcback();

		if (GetAnimateFrameback() >= 1)
		{

			SetAnimateFlag(3);

		}
	}
	if (GetAnimateFlag() == 3)
	{

		SetAnimateFrameback(-_aniframe);

		AnimateProcback();

		if (GetAnimateFrameback() < 0)
		{

			SetAnimateFlag(0);

		}

	}


}


