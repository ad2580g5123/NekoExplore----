#include "Quiver.h"

Quiver::Quiver()
{

	m_Model.Load("Data/CatsModel/Quiver.gltf");
	
}

Quiver::~Quiver()
{

	m_Model.Release();

}

void Quiver::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_MasterMat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}


const Math::Matrix& Quiver::GetMat()const
{

	return m_Mat;

}

Math::Matrix& Quiver::GetMasterMat()
{

	return m_MasterMat;

}


