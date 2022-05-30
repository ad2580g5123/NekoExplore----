#include "Headers.h"
PlayerStartScene::PlayerStartScene(StartScene* _scene, float _camAngX, float _camAngY,Math::Vector3 _pos)
{
    //BodyParts//
    m_StartScene = _scene;

    m_BodyPos = _pos;

    //Mouse//

    m_BaseMousePos = { ScrW / 2,ScrH / 2 };

    ClientToScreen(APP.m_window.GetWndHandle(), &m_BaseMousePos);

    SetCursorPos(m_BaseMousePos.x, m_BaseMousePos.y);

}
PlayerStartScene::~PlayerStartScene()
{
    //BodyParts//

    if (m_Head != nullptr)
    {
        delete m_Head;

        m_Head = nullptr;
    }

    if (m_RightHand != nullptr)
    {
        delete m_RightHand;

        m_RightHand = nullptr;
    }

    if (m_Bow != nullptr)
    {
        delete m_Bow;

        m_Bow = nullptr;
    }

    if (m_Quiver != nullptr)
    {
        delete m_Quiver;

        m_Quiver = nullptr;
    }

    if (m_LeftHand != nullptr)
    {
        delete m_LeftHand;

        m_LeftHand = nullptr;
    }

    if (m_RightFoot != nullptr)
    {
        delete m_RightFoot;

        m_RightFoot = nullptr;
    }

    if (m_LeftFoot != nullptr)
    {
        delete m_LeftFoot;

        m_LeftFoot = nullptr;
    }

    //Body//

    m_BodyModel.Release();

}
void PlayerStartScene::Update(float _camAngX, float _camAngY)
{

    m_BodyMat.Translation() = m_BodyPos;

    //Mouse//
    
    Mouse();

    //Body Parts Pos//

    SetBodyPartsPos();

    //Move//

    Move(_camAngX,_camAngY);

    //Check Ground//
    CheckGround();

    //Shoot//

    Shoot(_camAngX, _camAngY);

    //Jump//
    
    Jump();

    //Arrow//

    CheckArrow();

    //Door//
    CheckDoor();

}

void PlayerStartScene::CheckGround()
{

    Ground& ground = m_StartScene->GetGround();

    

    if (m_MoveFlag == true)
    {
        Math::Vector3 forwardVec;

        forwardVec = m_MoveVec;

        forwardVec.Normalize();

        float dis2 = FLT_MAX;

        bool ground_nomal;

        ground_nomal = ground.CheckHit(m_BodyPos, forwardVec, m_NormalVec, dis2);


        if (ground_nomal)
        {

            Math::Vector3 dot;

            dot = DirectX::XMVector3Dot(-forwardVec, m_NormalVec);

            float limit;

            limit = 2;

            if (dis2 < limit)
            {

                m_BodyPos += m_NormalVec * ((limit - dis2) / dot.x);

            }

        }
    }
   

    //Ground Ray//
    float dis_ground;

    bool groundhit;

    groundhit = ModelIntersects(ground.GetModel(), ground.GetMat(), m_BodyPos, { 0, -1, 0 }, dis_ground);


    if (groundhit)
    {

        if (m_BodyPos.y <= m_BodyPos.y + (2.0f - dis_ground))
        {

            m_BodyPos.y = m_BodyPos.y + (1.35f - dis_ground);

            m_Gravity = 0;
        }

    }

    if (m_Gravity == 0 && m_TounchGround == true)
    {
        m_SoundFallDown->InstancePlay();

        m_TounchGround = false;
    }
}

void PlayerStartScene::CheckArrow()
{
    
 

    for (UINT i = 0; i < m_Arrow.size(); i++)
    {
        m_Arrow[i]->Update();

        m_ArrowEffect[i]->Update(m_Arrow[i]->GetMat());

        if (m_Arrow[i]->Update() == false)
        {

            delete m_Arrow[i];

            delete m_ArrowEffect[i];

            m_Arrow.erase(m_Arrow.begin() + i);

            m_ArrowEffect.erase(m_ArrowEffect.begin() + i);

            i--;

        }

    }
}

void PlayerStartScene::CheckDoor()
{
    Door& door = m_StartScene->GetDoor();

    Math::Vector3 targetVec = GetPos() - door.GetMat().Translation();

    float dis = targetVec.Length();

    if (dis < m_Radius + door.GetRadius())
    {

        m_StartScene->SetSceneChangeFlag(true);

    }
}

void PlayerStartScene::Mouse()
{

    CameraStartScene& Camera = m_StartScene->GetStartSceneCamera();

    POINT MousePos;

    GetCursorPos(&MousePos);

    Camera.SetCameraAngleY((MousePos.x - m_BaseMousePos.x) / 32.0);

    Camera.SetCameraAngleX((MousePos.y - m_BaseMousePos.y) / 32.0);

    SetCursorPos(m_BaseMousePos.x, m_BaseMousePos.y);

}




