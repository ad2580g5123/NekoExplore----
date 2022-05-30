#include "SceneBase.h"
SceneBase::SceneBase()
{
}
SceneBase::~SceneBase()
{
	m_BlendAdd = D3D.CreateBlendState(KdBlendMode::Add);

	m_BlendAlpha = D3D.CreateBlendState(KdBlendMode::Alpha);

}

void SceneBase::Frame()
{
	// �Q�[?�X�V??

	Update();

	// �o�b�N�o�b�t�@�N?�A

	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(0.0f, 0.0f, 1.0f, 1));//RGBA��0-1�͈̔͂�

	// Z�o�b�t�@�N?�A

	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer()->GetDSView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	/*SetCamera();*/

	Draw();

}

void SceneBase::Update()
{
}

void SceneBase::Draw()
{
}

//void SceneBase::SetCamera()
//{
//
//}
