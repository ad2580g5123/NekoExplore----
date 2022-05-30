#include "Sky.h"
void Sky::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

Sky::Sky(std::string _modelname)
{

	m_Model.Load(_modelname); //Data / Sky / Sky.gltf

	m_Mat = Math::Matrix::Identity;

	m_Mat = DirectX::XMMatrixScaling(50, 50, 50);

}

Sky::~Sky()
{

	m_Model.Release();

}
