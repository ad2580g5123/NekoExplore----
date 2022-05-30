#include"Headers.h"
void StartScene::Update()
{

    if (m_SceneChangeFlag == false)
    {
        m_BgmPlayer->Update();
    }

    //Camrea//

    m_Camera->Update();

    //Player//

    m_Player->Update(m_Camera->GetCamreaAngleX(), m_Camera->GetCamreaAngleY());

    if (m_SceneChangeFlag == true)
    {
        m_SceneAlpha -= 0.02f;
    }

    if (m_SceneAlpha <= 0)
    {
        m_BgmPlayer->SetSoundInstanceStop();

        SOUNDMANAGER.AllDelete();

        SCENEMANAGER.ChangeScene(new GameScene());
    }

    //Door//
    m_Door->Update();

    //Target//

    m_Target->Update();

}

void StartScene::DynamicDraw()
{
    m_SubBuffer.SetRenderTarget();

    SHADER.m_standardShader.SetToDevice();

    SHADER.m_standardShader.SetLightEnable(false);

    //Sky//

    m_Sky->Draw();

    SHADER.m_standardShader.SetLightEnable(true);

    //Cmera ray hit position//

    const Math::Vector3& hitPos = m_Player->GetHitPos();

    Math::Matrix mat;

    mat = DirectX::XMMatrixTranslation(hitPos.x, hitPos.y, hitPos.z);

    SHADER.m_standardShader.SetWorldMatrix(mat);

     //Ground//

    m_Ground->Draw();

    //Door//

    m_Door->Draw();

    //Player//

    m_Player->Draw();

    //Arrow//
    for (UINT i = 0; i < m_ArrowCollection.size(); i++)
    {

        m_ArrowCollection[i]->Draw();

    }

    //Target//

    if(MOUSEONCLICK.GetClickKeyFlag()==true)
    {
        m_Target->Draw();
    }

}

void StartScene::Draw()
{
    D3D.SetBackBuffer();

    SHADER.m_spriteShader.Begin();

    Math::Rectangle rc = { 0, 0, ScrW, ScrH - m_ScenceMoveNum };

    SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

    SHADER.m_spriteShader.DrawTex(&m_SubBuffer, rc, m_SceneAlpha);

    SHADER.m_spriteShader.End();

}

StartScene::StartScene()
{

    ShowCursor(FALSE);

    srand(timeGetTime());

    //Light//

    SHADER.m_cb8_Light.Work().AmbientLight = { 1,1,1 };

    SHADER.m_cb8_Light.Write();

    //Sky//

    if (m_Sky == nullptr)
    {
        m_Sky = new Sky("Data/Sky/Sky.gltf");
    }

    //Camera//

    if (m_Camera == nullptr)
    {
        m_Camera = new CameraStartScene(this);
    }

    //Player//

    if (m_Player == nullptr)
    {
        m_Player = new PlayerStartScene(this, m_Camera->GetCamreaAngleX(), m_Camera->GetCamreaAngleY(),Math::Vector3(0, 1.35,0));
    }

    //Ground//

    if (m_Ground == nullptr)
    {
        m_Ground = new Ground("Data/GroundAll/StartScene/StartScene.gltf");
    }

    //Ground//

    if (m_Door == nullptr)
    {
        m_Door = new Door(0,1,160);
    }


    //Target//

    if (m_Target == nullptr)
    {
        m_Target = new Target();
    }

    //Font//

    m_SpriteFont = new DirectX::SpriteFont(D3D.GetDev(), L"Data/SpriteFont30.dat");

    //Sound//

    m_BgmPlayer = SOUNDMANAGER.AddSoundBgm("Data/Sound/StartSceneBgm.WAV");

    m_SubBuffer.CreateRenderTarget(ScrW, ScrH);

    //SceneChange//

    m_SceneAlpha = 1.0f;

    m_SceneChangeFlag = false;

    m_ScenceMoveNum = 0;

}

void StartScene::Frame()
{

    SHADER.m_cb8_Light.Work().PL_Num = 0;

    Update();

    SHADER.m_cb8_Light.Write();

    // バックバッファク?ア
    D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(0.0f, 0.0f, 0.0f, 1));//RGBAを0-1の範囲で

    //subbuffer clear
    D3D.GetDevContext()->ClearRenderTargetView(m_SubBuffer.GetRTView(), Math::Color(0.3f, 0.3f, 0.7f, 1));//RGBAを0-1の範囲で

    // Zバッファク?ア
    D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer()->GetDSView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

    //Camera//

    m_Camera->Frame();


    DynamicDraw();

    // ゲー?描画??
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

StartScene::~StartScene()
{
    //Sky//

    if (m_Sky != nullptr)
    {
        m_Sky->~Sky();

        delete m_Sky;
    }

    //Player//

    if (m_Sky != nullptr)
    {
        m_Player->~PlayerStartScene();

        delete m_Player;
    }


    //Ground//

    if (m_Ground != nullptr)
    {
        m_Ground->~Ground();

        delete m_Ground;
    }


    //Target//
    if (m_Target != nullptr)
    {

        m_Target->~Target();

        delete m_Target;

    }

    //Door//
    if (m_Door != nullptr)
    {

        m_Door->~Door();

        delete m_Door;

    }
}

int StartScene::GetScenceMoveNum()
{
    return m_ScenceMoveNum;
}

PlayerStartScene& StartScene::GetPlayer()const
{
    return* m_Player;
}

Ground& StartScene::GetGround()const
{
    return* m_Ground;
}

Door& StartScene::GetDoor() const
{
    return* m_Door;
}

CameraStartScene& StartScene::GetStartSceneCamera() const
{
    return* m_Camera;
}

void StartScene::SetScenceMoveNum(const int _num)
{
    m_ScenceMoveNum += _num;

    if (m_ScenceMoveNum >= 100)
    {
        m_ScenceMoveNum = 100;
    }
    if (m_ScenceMoveNum <= 0)
    {
        m_ScenceMoveNum = 0;
    }
}

void StartScene::SetSceneChangeFlag(const bool _val)
{
    m_SceneChangeFlag = _val;
}


