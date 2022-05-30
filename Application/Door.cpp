#include "Headers.h"
Door::Door(const float _x, const float _y, const float _z)
{

	m_Model.Load("Data/GroundAll/StartScene/Door/Door.gltf");

	m_Mat = DirectX::XMMatrixTranslation(_x, _y, _z);

	m_Radius = 3;

}

Door::~Door()
{

	m_Model.Release();

}

void Door::Draw()
{
	SHADER.m_standardShader.SetUVOffset(m_UvOffSet);

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(&m_Model);

	SHADER.m_standardShader.SetUVOffset(Math::Vector2(0, 0));
}

void Door::Update()
{
	m_UvOffSet.y -= 0.02f;
}

const Math::Matrix& Door::GetMat() const
{

	return m_Mat;

}

const KdModel& Door::GetModel() const
{

	return m_Model;

}


const float& Door::GetRadius() const
{

	return m_Radius;

}

void Door::SetPos(const Math::Vector3 _vec)
{

	m_Mat.Translation() = _vec;

}