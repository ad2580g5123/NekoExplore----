#include "Head.h"
Head::Head()
{

	m_Model.Load("Data/CatsModel/head.gltf");

}

Head::~Head()
{

	m_Model.Release();

}

void Head::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

Math::Matrix& Head::GetMat()
{

	return m_Mat;

}


