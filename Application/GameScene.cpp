#include "main.h"
#include "define.h"
#include"Headers.h"
void GameScene::Update()
{

   //Camrea//
   
   m_Camera->Update();

   //Player//

   m_Player->Update(m_Camera->GetCamreaAngleX(), m_Camera->GetCamreaAngleY());
    
   //QuickSand//
   m_QuickSand->Update();

   //Pushcrystal//
   m_PushCrystal->Update();

   //Stairs//
   for(int i=0;i<2;i++)
   {
       if (m_Button[i]->GetPushedFlag() == true)
       {

           m_Stair[i]->Update();

       }
   }

   //Button
   for(int i=0;i<2;i++)
   {
       if (m_Button[i]->GetFlag() == true)
       {
           m_Button[i]->Update();
       }
   }

   //Target//

   m_Target->Update();

   //Treasure//

   m_Treasure->Update();

   //CheckSceneChange//

   CheckSceneChange();
}

void GameScene::DynamicDraw()
{   
    m_SubBuffer.SetRenderTarget();

    SHADER.m_standardShader.SetToDevice();

    SHADER.m_standardShader.SetLightEnable(false);

    //Sky//

    m_Sky->Draw();

    SHADER.m_standardShader.SetLightEnable(true);

     //Ground//

    m_Ground->Draw();

    //PushCrystal//

    m_PushCrystal->Draw();

    //Button//
    for (int i = 0; i < 2; i++)
    {
        m_Button[i]->Draw();
    }

    //Stairs//
    for (int i = 0; i < 2; i++)
    {
        m_Stair[i]->Draw();
    }


    //QuickSand//

    m_QuickSand->Draw();

    //Treasure//

    m_Treasure->Draw();

    //Player//

    m_Player->Draw();

    //Target//

    if (MOUSEONCLICK.GetClickKeyFlag() == true)
    {
        m_Target->Draw();
    }

}

void GameScene::Draw()
{
    D3D.SetBackBuffer();

    SHADER.m_spriteShader.Begin();


    Math::Rectangle rc = { 0, 0, ScrW, ScrH - m_ScenceMoveNum };

    SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

    SHADER.m_spriteShader.DrawTex(&m_SubBuffer, rc, m_SceneAlpha);

    SHADER.m_spriteShader.End();

}

GameScene::GameScene()
{

   ShowCursor(FALSE);

   srand(timeGetTime());

   //Light//

   SHADER.m_cb8_Light.Work().AmbientLight = { 1,1,1 };

   SHADER.m_cb8_Light.Write();

   //Sky//

   if(m_Sky==nullptr)
   {
       m_Sky = new Sky("Data/Skyinside/Sky.gltf");
   }

   //Camera//

   if (m_Camera == nullptr)
   {
       m_Camera = new CameraGameScene(this);
   }

   //Player//

   if (m_Player == nullptr) 
   {
       m_Player = new PlayerGameScene(this, m_Camera->GetCamreaAngleX(), m_Camera->GetCamreaAngleY(),Math::Vector3(0, 1.35, -200));
   }

   //Ground//

   if (m_Ground == nullptr) 
   {
       m_Ground = new Ground("Data/GroundAll/PyramidInside/PyramidInside2.gltf");
   }

   //PushCrystal//

   if (m_PushCrystal == nullptr)
   {
       m_PushCrystal = new PushCrystal(this);
   }

   //Button/

   m_Button[0] = new Button(-30,0, -160,0,0);

   m_Button[1] = new Button(47.0, 22.25, -56.25, -90,90);
  
   //QuickSand//

   if (m_QuickSand == nullptr)
   {
       m_QuickSand = new QuickSand(this);
   }

   //Treasure//

   if (m_Treasure == nullptr)
   {
       m_Treasure = new Treasure(this);
   }

   //Target//

   if (m_Target == nullptr)
   {
       m_Target = new Target();
   }


   //Font//

   m_SpriteFont = new DirectX::SpriteFont(D3D.GetDev(), L"Data/SpriteFont30.dat");


   //stairs//

   m_Stair[0] = new Stairs(Math::Vector3(53, -11, -120), Math::Vector3(-30, -11, -120));

   m_Stair[1] = new Stairs(Math::Vector3 (-55, -11, -90), Math::Vector3(30, -11, -90));


   //Sound//

   m_BgmPlayer = SOUNDMANAGER.AddSoundBgm("Data/Sound/GameSceneBgm.WAV");

   m_SubBuffer.CreateRenderTarget(ScrW, ScrH);

   //SceneChange//

   m_SceneAlpha = 1.0f;

   m_SceneChangeFlag = false;

   m_ScenceMoveNum = 0;

}

void GameScene::Frame()
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

GameScene::~GameScene()
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
        m_Player->~PlayerGameScene();

        delete m_Player;
    }

    //Stairs//

    for (int i = 0; i < 2; i++)
    {
        m_Stair[i]->~Stairs();

        delete m_Stair[i];
    }

    //Ground//

    if (m_Ground != nullptr)
    {
        m_Ground->~Ground();

        delete m_Ground;
    }

    //QuickSand//
    if (m_QuickSand != nullptr)
    {
        m_QuickSand->~QuickSand();

        delete m_QuickSand;
    }

    //Treasure
    if (m_Treasure != nullptr)
    {
        m_Treasure->~Treasure();

        delete m_Treasure;
    }

    //PushCrystal//

    if (m_PushCrystal != nullptr) 
    {
        m_PushCrystal->~PushCrystal();
   
        delete m_PushCrystal;
    }

    //Target//
    if(m_Target != nullptr)
    {

        m_Target->~Target();

        delete m_Target;

    }

    //Button//
    for (int i = 0; i < 2; i++) 
    {
        m_Button[i]->~Button();

        delete m_Button[i];
    }

}

int GameScene::GetScenceMoveNum()
{
    return m_ScenceMoveNum;
}

PlayerGameScene& GameScene::GetPlayer()const
{
    return *m_Player;
}

Ground& GameScene::GetGround()const
{
    return*m_Ground;
}

PushCrystal& GameScene::GetPushCrystal() const
{
    return* m_PushCrystal;
}


Stairs& GameScene::GetStair(int _num)const
{
    return* m_Stair[_num];
}
Button& GameScene::GetButton(int _num) const
{
    return* m_Button[_num];
}

QuickSand& GameScene::GetQuickSand() const
{
    return* m_QuickSand;
}

CameraGameScene& GameScene::GetCamera() const
{
    return* m_Camera;
}

void GameScene::SetScenceMoveNum(const int _num)
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

void GameScene::CheckSceneChange()
{

    if (m_SceneChangeFlag == false)
    {
        m_BgmPlayer->Update();
    }

    if (m_SceneChangeFlag == true)
    {
        m_SceneAlpha -= 0.02f;

    }

    if (m_Treasure->GetAnimateWaitTime() > 120)
    {
        m_SceneChangeFlag = true;

        if (m_SceneAlpha <= 0)
        {
            m_BgmPlayer->SetSoundInstanceStop();

            SOUNDMANAGER.AllDelete();

            SCENEMANAGER.ChangeScene(new ClearScene());
        }

    }

    if (m_Player->GetPlayerDeathFlag() == true)
    {

        m_SceneChangeFlag = true;

        if (m_SceneAlpha <= 0)
        {
            m_BgmPlayer->SetSoundInstanceStop();

            SOUNDMANAGER.AllDelete();

            SCENEMANAGER.ChangeScene(new GameOverScene());
        }

    }
}



