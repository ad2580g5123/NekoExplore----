#include "Headers.h"

Target::Target()
{

	m_Tex.Load("Data/Target/CrossOutSide.png");

	m_TexCenter.Load("Data/Target/CrossCenter.png");

	m_Mat = Math::Matrix::Identity;

	m_PosMat = DirectX::XMMatrixTranslation(0,-90,0);

	m_MatCenter = DirectX::XMMatrixTranslation(0, -90, 0);

	m_ScaleNum = 7;
}

Target::~Target()
{

	m_Tex.Release();
	
}

void Target::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_ScaleNum -= 0.15f;

		if (m_ScaleNum < 1.0f)
		{
			m_ScaleNum = 1.0f;
		}

	}else
	{	
		m_ScaleNum = 7.0f;
	}

	m_ScaleMat = DirectX::XMMatrixScaling(m_ScaleNum, m_ScaleNum, 1.0f);

	m_Mat =  m_ScaleMat* m_PosMat;

}

void Target::Draw()
{

	SHADER.m_spriteShader.SetMatrix(m_Mat);

	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 66, 66), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_MatCenter);

	SHADER.m_spriteShader.DrawTex(&m_TexCenter, Math::Rectangle(0, 0, 66, 66), 1.0f);

}
