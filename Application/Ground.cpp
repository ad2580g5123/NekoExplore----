#include "Headers.h"

Ground::Ground(std::string _modelname)
{

	m_Model.Load(_modelname);

	m_Mat = Math::Matrix::Identity;

}
Ground::~Ground()
{

	m_Model.Release();

}

void Ground::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

const KdModel& Ground::GetModel()const
{

	return m_Model;

}

const Math::Matrix& Ground::GetMat()const
{

	return m_Mat;

}

bool Ground::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, Math::Vector3& _normalVec, float& _dis) const
{
	bool hit;

	hit = ModelIntersects2(m_Model, m_Mat, _rayPos, _normalVec, _rayVec, _dis);

	return hit;
}