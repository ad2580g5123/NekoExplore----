#include "Headers.h"

void EffectModel::Update(const Math::Matrix& _posmat)
{

	m_Mat = _posmat;

}

void EffectModel::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(&m_Model);

}

EffectModel::EffectModel(const Math::Matrix& _posmat, std::string _fileName)
{
	m_Model.Load(_fileName);

	m_Mat = _posmat;

}

EffectModel::~EffectModel()
{
	
	m_Model.Release();

}
