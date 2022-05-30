#include "Headers.h"

CameraGameScene::CameraGameScene(GameScene* _scene)
{
    m_Scene = _scene;
    //Camera//

    m_RotY = 0;

    m_RotX = 0;

    m_WaitTime = 300;

    m_Pos = {};

    m_CameraChangeFlag = false;
}

void CameraGameScene::Update()
{
    PlayerGameScene& player = m_Scene->GetPlayer();
    //Setting Camera Limit//

    CameraLimit();

    //Check Camera Chamge Wait Time//
    CheckCameraChangeWaitTime();

    ShootCameraChangeReturn();

}

void CameraGameScene::Frame()
{
    PlayerGameScene& player = m_Scene->GetPlayer();

    PushCrystal& pushcrystal = m_Scene->GetPushCrystal();

    Math::Matrix tmpRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_RotY));

    Math::Matrix tmpRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_RotX));

    Math::Matrix Rotmat = tmpRotX * tmpRotY;

    m_Pos = DirectX::XMVector3TransformCoord(Math::Vector3(0, 5, -14+m_CameraPosZ), Rotmat);
    
    m_Pos += Math::Vector3(player.GetMat().Translation().x, CameraPosYFllow(), player.GetMat().Translation().z);

    m_Look = Math::Vector3(player.GetMat().Translation().x, CameraPosYFllow()+5, player.GetMat().Translation().z);

    SHADER.m_cb7_Camera.Work().mV = DirectX::XMMatrixLookAtLH
    (

        m_Pos,

        m_Look,

        Math::Vector3(0, 1, 0)
    );

    //quicksand camerachage//

    if (pushcrystal.GetMat()._42 <= 0 && m_WaitTime > 0)
    {
        m_CameraChangeFlag = true;

        Math::Vector3 camPos = Math::Vector3(-100, 5, 101);

        Math::Vector3  camLook = Math::Vector3(-100, 10, 115);

        SHADER.m_cb7_Camera.Work().mV = DirectX::XMMatrixLookAtLH
        (

            camPos,

            camLook,

            Math::Vector3(0, 1, 0)
        );

    }

    SHADER.m_cb7_Camera.Work().CamPos = SHADER.m_cb7_Camera.Work().mV.Invert().Translation();

    //ŽË‰es—ñ
    SHADER.m_cb7_Camera.Work().mP = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)ScrW / (float)ScrH, 0.01f, 2000.0f);

    //ƒr?[s—ñEŽË‰es—ñ‚ðGPU‚É“]?
    SHADER.m_cb7_Camera.Write();
}


float CameraGameScene::CameraPosYFllow()
{
    PlayerGameScene& player = m_Scene->GetPlayer();

    float y;

    y = player.GetMat().Translation().y;

   
    if (player.GetMat().Translation().y < -15 && player.GetMat().Translation().z < 300)
    {

        y = -15;

    }

    if (player.GetMat().Translation().y < -142 && player.GetMat().Translation().x<-291 && player.GetMat().Translation().x>-733)
    {

        y = -142;

    }
    return y;
}

void CameraGameScene::CheckCameraChangeWaitTime()
{
    if (m_WaitTime > 0 && m_CameraChangeFlag == true)
    {
        m_Scene->SetScenceMoveNum(2);
    }
    if (m_WaitTime <= 0 && m_CameraChangeFlag == true)
    {
        m_Scene->SetScenceMoveNum(-2);
    }
}


