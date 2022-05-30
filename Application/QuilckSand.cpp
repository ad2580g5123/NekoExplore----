#include "Headers.h"

QuickSand::QuickSand(GameScene* _scene)
{
	m_Scene = _scene;

	m_Model.Load("Data/GroundAll/QuickSand/QuickSand.gltf");

	m_Mat = Math::Matrix::Identity;

	m_Flag = true;

	m_Alpha = 1;

}
QuickSand::~QuickSand()
{
	m_Model.Release();
}
void QuickSand::Update()
{
	if (m_Flag == false)
	{
		m_Model.Release();
	}
	PushCrystal& pushcrystal = m_Scene->GetPushCrystal();

	CameraGameScene& camera = m_Scene->GetCamera();

	if (m_Flag == true)
	{
	m_UvOffSet.y -= 0.01f;
	}

	if (pushcrystal.GetMat()._42 <= 0)
	{

		SetAlpha(-0.005);

		if (GetAlpha() == 0)
		{

			SetFlag(false);

		}

		camera.SetCameraWaitTime(-1);

	}

}
void QuickSand::Draw()
{

	if (m_Flag == true)
	{

	SHADER.m_standardShader.SetUVOffset(m_UvOffSet);

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(&m_Model,m_Alpha);

	SHADER.m_standardShader.SetUVOffset(Math::Vector2(0,0));

	}
	
}

const KdModel& QuickSand::GetModel()const
{

	return m_Model;

}

const Math::Matrix& QuickSand::GetMat()const
{

	return m_Mat;

}

const float& QuickSand::GetAlpha() const
{

	return m_Alpha;

}

void QuickSand::SetFlag(const bool _flag)
{

	m_Flag = _flag;

}

void QuickSand::SetAlpha(float _alpha)
{

	m_Alpha += _alpha;

	if(m_Alpha<0)
	{

		m_Alpha = 0;

	}

}


bool QuickSand::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, Math::Vector3& _normalVec, float& _dis) const
{
	bool hit;

	hit = ModelIntersects2(m_Model, m_Mat, _rayPos, _normalVec, _rayVec, _dis);

	return hit;
}
