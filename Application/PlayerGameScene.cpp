#include "Headers.h"
PlayerGameScene::PlayerGameScene(GameScene* _gamescene, float _camAngX, float _camAngY,Math::Vector3 _pos)
{
    //BodyParts//
    m_GameScene = _gamescene;

    m_BodyPos = _pos; //0, 1.35, -200

    //DeathTime//

    m_DeathTimeCount = 0;

    m_PlayerDeathFlag = false;

    m_MovePower = 0.5f;

    m_StairsDis = 0;

    m_GroundDis = 0;

    //Mouse//

    m_BaseMousePos = { ScrW / 2,ScrH / 2 };

    ClientToScreen(APP.m_window.GetWndHandle(), &m_BaseMousePos);

    SetCursorPos(m_BaseMousePos.x, m_BaseMousePos.y);

}
PlayerGameScene::~PlayerGameScene()
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
void PlayerGameScene::Update(float _camAngX, float _camAngY)
{
    //Object//

    m_BodyMat.Translation() = m_BodyPos;

    //Mouse//
  
     Mouse(); 

    //Body Parts Pos//

    SetBodyPartsPos();

    //Move//

    Move(_camAngX,_camAngY);

    //Shoot//
  
    Shoot(_camAngX, _camAngY);
   
    //Jump//

    Jump();

    //Checkground//

    CheckGround();

    //Arrow//

    CheckArrow();

    //Burron//
    CheckButton();
       
    //DeathTimeCount//
    CheckDeathTime();

}

const bool& PlayerGameScene::GetPlayerDeathFlag() const
{
    return m_PlayerDeathFlag;
}

const float& PlayerGameScene::GetPlayerDeathTimeCount() const
{
    return m_DeathTimeCount;
}

const float& PlayerGameScene::GetMovePower() const
{
    return m_MovePower;
}

const float& PlayerGameScene::GetGroundDis() const
{
    return m_GroundDis;
}

const float& PlayerGameScene::GetStairDis() const
{
    return m_StairsDis;
}

void PlayerGameScene::CheckGround()
{
    Ground& ground = m_GameScene->GetGround();

    Stairs& stair0 = m_GameScene->GetStair(0);

    Stairs& stair1 = m_GameScene->GetStair(1);

    Stairs* stairs[2] = { &stair0 ,&stair1 };

    QuickSand& quicksand = m_GameScene->GetQuickSand();


    //forward check//
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

    if (m_MoveFlag == true)
    {

        Math::Vector3 forwardVec;

        forwardVec = m_MoveVec;

        forwardVec.Normalize();

        float dis2 = FLT_MAX;

        bool sand_nomal;

        sand_nomal = quicksand.CheckHit(m_BodyPos, forwardVec, m_NormalVec, dis2);


        if (sand_nomal)
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
    //ray direct down check//

    bool groundhit;


    groundhit = ModelIntersects(ground.GetModel(), ground.GetMat(), m_BodyPos, { 0, -1, 0 }, m_GroundDis);


    if (groundhit)
    {

        if (m_BodyPos.y <= m_BodyPos.y + (2.0f - m_GroundDis))
        {

            m_BodyPos.y = m_BodyPos.y + (1.35f - m_GroundDis);

            m_Gravity = 0;

            m_DeathTimeCount = 0;

        }

    }
    else
    {
        m_GroundDis = 0;
    }

    bool stairshit;

    for (int i = 0; i < 2; i++)
    {

        stairshit = ModelIntersects(stairs[i]->GetModel(), stairs[i]->GetMat(), m_BodyPos, { 0, -1, 0 }, m_GroundDis);

        if (stairshit)
        {

            if (m_BodyPos.y <= m_BodyPos.y + (2.0f - m_GroundDis))
            {

                m_BodyPos.y = m_BodyPos.y + (1.35f - m_GroundDis);

                m_Gravity = 0;

                m_DeathTimeCount = 0;

                m_BodyPos.x += stairs[i]->GetMoveScale().x;


            }

        }

    }

    m_DeathTimeCount++;

    if (m_Gravity == 0 && m_TounchGround == true)
    {
        m_SoundFallDown->InstancePlay();

        m_TounchGround = false;
    }
}

void PlayerGameScene::CheckButton()
{
    Button& button0 = m_GameScene->GetButton(0);

    Button& button1 = m_GameScene->GetButton(1);

    Button* buttonobj[2] = { &button0 ,&button1 };

    for (int x = 0; x < 2; x++)
    {
        if (buttonobj[x]->GetFlag() == true)
        {

            Math::Vector3 targetVec = GetPos() - buttonobj[x]->GetMat().Translation();

            float disbutton = targetVec.Length();

            if (disbutton < m_Radius + buttonobj[x]->GetRadius())
            {

                buttonobj[x]->SetPushedFlag(true);

            }
        }
    }
}

void PlayerGameScene::CheckArrow()
{
  

    Button& button0 = m_GameScene->GetButton(0);

    Button& button1 = m_GameScene->GetButton(1);

    Button* buttonobj[2] = { &button0 ,&button1 };

    for (UINT i = 0; i < m_Arrow.size(); i++)
    {

        for (int x = 0; x < 2; x++)
        {
            if (buttonobj[x]->GetFlag() == true)
            {

                float dis;

                Math::Vector3 LookVec = (m_Arrow[i]->GetMat().Translation() - buttonobj[x]->GetMat().Translation());

                dis = LookVec.Length();

                if (dis < m_Arrow[i]->GetRadius() + buttonobj[x]->GetRadius())
                {

                    buttonobj[x]->SetPushedFlag(true);

                    m_Arrow[i]->SetFlag(false);

                }
            }

        }


    }
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

void PlayerGameScene::CheckDeathTime()
{

    if (m_DeathTimeCount >= 180)
    {
        m_PlayerDeathFlag = true;
    }

}

void PlayerGameScene::Mouse()
{
  
    CameraGameScene& Camera = m_GameScene->GetCamera();

    POINT MousePos;

    GetCursorPos(&MousePos);

    Camera.SetCameraAngleY((MousePos.x - m_BaseMousePos.x) / 32.0);


    Camera.SetCameraAngleX((MousePos.y - m_BaseMousePos.y) / 32.0 );

    SetCursorPos(m_BaseMousePos.x, m_BaseMousePos.y);

}


const float& PlayerGameScene::GetCount()const
{
    return m_DeathTimeCount;

}


