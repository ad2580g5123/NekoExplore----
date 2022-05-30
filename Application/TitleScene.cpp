#include "Headers.h"
TitleScene::~TitleScene()
{

	m_Tex.Release();

	m_EnterTex.Release();

	m_TitleTex.Release();


}

TitleScene::TitleScene()
{

	m_Tex.Load("Data/Texture/desertTitle.png");

	BackX = 0;

	m_TitleTex.Load("Data/Texture/nekoexplore.png");

	m_EnterTex.Load("Data/Texture/Enter.png");

	m_BgmPlayer = SOUNDMANAGER.AddSoundBgm("Data/Sound/TitleBgm.WAV");

	m_SubBuffer.CreateRenderTarget(ScrW, ScrH);

	m_SceneAlpha = 1.0f;

	m_SceneChangeFlag = false;
}

void TitleScene::Draw()
{
	D3D.SetBackBuffer();
	
	SHADER.m_spriteShader.Begin();

	Math::Rectangle rc = { 0, 0, ScrW, ScrH };

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	SHADER.m_spriteShader.DrawTex(&m_SubBuffer, rc, m_SceneAlpha);
	
	SHADER.m_spriteShader.End();

}

void TitleScene::DynamicDraw()
{
	m_SubBuffer.SetRenderTarget();

	SHADER.m_spriteShader.Begin();

	//SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	//SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1920, 1072), 1.0f);

	m_Mat = DirectX::XMMatrixTranslation(BackX + 1280, 0, 0);

	SHADER.m_spriteShader.SetMatrix(m_Mat);

	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	//background left//

	m_Mat = DirectX::XMMatrixTranslation(BackX, 0, 0);

	SHADER.m_spriteShader.SetMatrix(m_Mat);

	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	m_TitleMat = DirectX::XMMatrixTranslation(0, 90, 0);

	SHADER.m_spriteShader.SetMatrix(m_TitleMat);

	SHADER.m_spriteShader.DrawTex(&m_TitleTex, Math::Rectangle(0, 0, 998, 127), 1.0f);

	m_EnterMat = DirectX::XMMatrixTranslation(0, -160, 0);

	SHADER.m_spriteShader.SetMatrix(m_EnterMat);

	SHADER.m_spriteShader.DrawTex(&m_EnterTex, Math::Rectangle(0, 0, 391, 63), 1.0f);

	SHADER.m_spriteShader.End();


}

void TitleScene::Update()
{
	if (m_SceneChangeFlag == false)
	{
		m_BgmPlayer->Update();
	}
	
	BackX -= 0.5;

	if (BackX < -1280)
	{

		BackX += 1280;

	}

	SOUNDMANAGER.Update();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_SceneChangeFlag = true;
		if (SYSTEM.GetClickKeyFlag() == false)
		{
			m_SoundClick = SOUNDMANAGER.AddSoundEffect("Data/Sound/Click.WAV");

			m_SoundClick->InstancePlay();

			SYSTEM.SetClickKeyFlag(true);
		}
	}
	else
	{
		SYSTEM.SetClickKeyFlag(false);
	}

	if (m_SceneChangeFlag == true)
	{
		m_SceneAlpha -= 0.02f;

		m_BgmPlayer->SetSoundInstanceStop();
	}

	if (m_SceneAlpha <= 0)
	{
		SOUNDMANAGER.AllDelete();

		SCENEMANAGER.ChangeScene(new StartScene());
	}

}

void TitleScene::Frame()
{
	// �Q�[?�X�V??
	Update();

	// �o�b�N�o�b�t�@�N?�A
	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(0.0f, 0.0f, 0.0f, 1));//RGBA��0-1�͈̔͂�
	//subbuffer clear
	D3D.GetDevContext()->ClearRenderTargetView(m_SubBuffer.GetRTView(), Math::Color(0.3f, 0.3f, 0.7f, 1));//RGBA��0-1�͈̔͂�
	// Z�o�b�t�@�N?�A
	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer()->GetDSView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	DynamicDraw();
	// �Q�[?�`��??
	Draw();
	
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = ScrW;
	vp.Height = ScrH;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	D3D.GetDevContext()->RSSetViewports(1, &vp);
	D3D.GetDevContext()->OMSetRenderTargets(1,
		D3D.GetBackBuffer()->GetRTViewAddress(),
		D3D.GetZBuffer()->GetDSView());
}
