#include "Headers.h"

ShootMode::ShootMode()
{

	m_Tex.Load("Data/ShootMode/Shoot1.png");

}

ShootMode::~ShootMode()
{

	m_Tex.Release();

}

void ShootMode::Draw()
{

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

}
