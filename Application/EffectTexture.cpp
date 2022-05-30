#include "Headers.h"

void EffectTexture::Update(const Math::Matrix& _posmat)
{
	for (int i = 9; i >= 0; i--)
	{

		m_Mat[i] = m_Mat[i - 1];

	}

	m_Mat[0] = _posmat;

	Vertex v[20];

	for (int i = 0; i < 10; i++)
	{
		v[i * 2 + 0].pos = DirectX::XMVector3TransformCoord(Math::Vector3(-1, 0, 0), m_Mat[i]);

		v[i * 2 + 1].pos = DirectX::XMVector3TransformCoord(Math::Vector3(1, 0, 0), m_Mat[i]);

		v[i * 2 + 0].color = { 1,1,1,1 };

		v[i * 2 + 1].color = { 1,1,1,1 };

		v[i * 2 + 0].uv = { 0,(float)i / 9.0f };

		v[i * 2 + 1].uv = { 1,(float)i / 9.0f };
	}

	m_Vb.WriteData(&v[0], sizeof(v));
}

void EffectTexture::Draw()
{

	UINT stride = sizeof(Vertex);

	UINT offset = 0;

	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_Vb.GetAddress(), &stride, &offset);

	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_Tex.GetSRViewAddress());

	//Left//
	// 
	//set matrix//
	SHADER.m_effectShader.SetWorldMatrix(Math::Matrix::Identity);

	//effectShader reflect to WriteToCB//

	SHADER.m_effectShader.WriteToCB();

	D3D.GetDevContext()->Draw(20, 0);//100vertex//
	
}

EffectTexture::EffectTexture(const Math::Matrix& _posmat)
{
	m_Tex.Load("Data/Effect/Effect1.bmp");

	for (int i = 0; i < 10; i++)
	{
		m_Mat[i] = _posmat;
	}
	Vertex v[20];

	D3D11_SUBRESOURCE_DATA srd = {};

	srd.pSysMem = &v[0];

	m_Vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DYNAMIC, &srd);

}

EffectTexture::~EffectTexture()
{

	m_Tex.Release();

	m_Vb.Release();

}
