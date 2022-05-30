#include"Billboard.h"
void Billboard::Update()
{
	Vertex v[4];
	v[0].pos = { -2.0f, 2.0f,0 };
	v[1].pos = { 2.0f, 2.0f,0 };
	v[2].pos = { -2.0f,-2.0f,0 };
	v[3].pos = { 2.0f,-2.0f,0 };
	v[0].color = { 1,1,1,1 };
	v[1].color = { 1,1,1,1 };
	v[2].color = { 1,1,1,1 };
	v[3].color = { 1,1,1,1 };

	/*v[0].uv = {0,0};
	v[1].uv = { 1,0 };
	v[2].uv = { 0,1 };
	v[3].uv = { 1,1 };*/
	if(m_animate>64)
	{
		m_animate=0;
	}
	int w = m_tex.GetWidth();
	int h = m_tex.GetHeight();
	float w1 = m_animate%8 * 32.0f / m_tex.GetWidth();
	float h1 = m_animate/8 * 32.0f/ m_tex.GetHeight();
	float w2 = (m_animate%8 + 1) * 32.0f / m_tex.GetWidth();
	float h2 = (m_animate/8 + 1) * 32.0f / m_tex.GetHeight();
	m_animate++;
	v[0].uv = { w1,h1 };
	v[1].uv = { w2,h1 };
	v[2].uv = { w1,h2 };
	v[3].uv = { w2,h2 };
	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = &v[0];
	m_vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);
	//BILLBORAD
	Math::Matrix tmpMat;

	tmpMat = SHADER.m_cb7_Camera.Work().mV;

	tmpMat._41 = 0;
	tmpMat._42 = 0;
	tmpMat._43 = 0;

	tmpMat = tmpMat.Invert();
	Math::Matrix posMat = DirectX::XMMatrixTranslation(0, 5, 0);

	m_mat = tmpMat * posMat;
}
void Billboard::Draw()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_vb.GetAddress(), &stride, &offset);

	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_tex.GetSRViewAddress());

	//set matrix//
	SHADER.m_effectShader.SetWorldMatrix(m_mat);
	//effectShader reflect to WriteToCB//
	SHADER.m_effectShader.WriteToCB();
	D3D.GetDevContext()->Draw(4, 0);//4vertex//
}
void Billboard::Init()
{
	m_tex.Load("Data/Texture/Smoke.png");

	m_mat = DirectX::XMMatrixTranslation(0, 0, 0);
	m_animate = 0;
}

void Billboard::Release()
{
	m_tex.Release();
	m_vb.Release();

}

