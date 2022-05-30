#include "Headers.h"
PlayerBase::PlayerBase()
{
    //BodyParts//

    if (m_Head == nullptr)
    {
        m_Head = new Head();
    }

    if (m_RightHand == nullptr)
    {
        m_RightHand = new RightHand();
    }

    if (m_Bow == nullptr)
    {
        m_Bow = new Bow();
    }

    if (m_Quiver == nullptr)
    {
        m_Quiver = new Quiver();
    }

    if (m_LeftHand == nullptr)
    {
        m_LeftHand = new LeftHand();
    }

    if (m_RightFoot == nullptr)
    {
        m_RightFoot = new RightFoot();
    }

    if (m_LeftFoot == nullptr)
    {
        m_LeftFoot = new LeftFoot();
    }

    //Body//

    m_BodyModel.Load("Data/CatsModel/Body.gltf");

    //Move//

    m_MoveAngle = 0;

    //Player Radius//

    m_Radius = 2.5f;

    //Gravity//

    m_Gravity = 0;

    //Shoot//

    m_ShootFlag = false;

    m_ShootSoundFlag = false;

    m_ShootAnimateFlag = false;

    m_ShootWaitTime = 0;

    //Jump//

    m_JumpFlag = false;


    //Sound//

    m_SoundMoveFlag = true;

    m_SoundArrow = SOUNDMANAGER.AddSoundEffect("Data/Sound/ArrowShoot.WAV");

    m_SoundShoot = SOUNDMANAGER.AddSoundEffect("Data/Sound/BowSound.wav");

    m_SoundMove = SOUNDMANAGER.AddSoundEffect("Data/Sound/Move.wav");

    m_SoundJump = SOUNDMANAGER.AddSoundEffect("Data/Sound/Jump.wav");

    m_SoundFallDown = SOUNDMANAGER.AddSoundEffect("Data/Sound/FallDown.wav");

    //Touching Ground//
    
    m_TounchGround = false;
    
    Math::Matrix PosMat = DirectX::XMMatrixTranslation(m_BodyMat._41 - 0.5, m_BodyMat._42, m_BodyMat._43);
    
    //blend//
    m_BlendAdd = D3D.CreateBlendState(KdBlendMode::Add);

    m_BlendAlpha = D3D.CreateBlendState(KdBlendMode::Alpha);

}
PlayerBase::~PlayerBase()
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
void PlayerBase::Update(float _camAngX, float _camAngY)
{
}

void PlayerBase::Draw()
{
    //Body Parts//

    if (m_Head != nullptr)
    {
        m_Head->Draw();
    }

    if (m_RightHand != nullptr)
    {
        m_RightHand->Draw();
    }

    if (m_Bow != nullptr)
    {
        m_Bow->Draw();
    }

    if (m_Quiver != nullptr)
    {
        m_Quiver->Draw();
    }

    if (m_LeftHand != nullptr)
    {
        m_LeftHand->Draw();
    }
    if (m_RightFoot != nullptr)
    {
        m_RightFoot->Draw();
    }
    if (m_LeftFoot != nullptr)
    {
        m_LeftFoot->Draw();
    }

    //Body//

    SHADER.m_standardShader.SetWorldMatrix(m_BodyMat);

    SHADER.m_standardShader.DrawModel(&m_BodyModel);

    //Arrow//
    SHADER.m_effectShader.SetToDevice();

    D3D.GetDevContext()->OMSetBlendState(m_BlendAdd, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);

  
    for (UINT i = 0; i < m_Arrow.size(); i++)
    {

        m_ArrowEffect[i]->Draw();

    }

    D3D.GetDevContext()->OMSetBlendState(m_BlendAlpha, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
}


const Math::Matrix& PlayerBase::GetMat()const
{
    return m_BodyMat;
}

const float& PlayerBase::GetRadius()const
{

    return m_Radius;

}

const Math::Vector3 PlayerBase::GetLookVec(const float _camAngX, const float _camAngY)const
{

    Math::Matrix rotMat;

    rotMat = DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(_camAngX), DirectX::XMConvertToRadians(_camAngY), 0);

    Math::Vector3 lookVec;

    lookVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), rotMat);

    return lookVec;

}

const KdModel& PlayerBase::GetModel()const
{

    return m_BodyModel;

}

const Math::Vector3& PlayerBase::GetPos()const
{

    return m_BodyPos;

}

const Math::Vector3& PlayerBase::GetMoveVec()const
{

    return m_MoveVec;

}
const const Math::Vector3& PlayerBase::GetHitPos()const
{

    return m_HitPos;

}


const float& PlayerBase::GetrayDis()const
{

    return m_RayDis;

}
void PlayerBase::SetPos(const Math::Vector3 _pos)
{

    m_BodyPos = _pos;

}

void PlayerBase::SetBodyPartsPos()
{
    m_BodyRot = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_MoveAngle));

    m_BodyTrans = DirectX::XMMatrixTranslation(m_BodyPos.x, m_BodyPos.y, m_BodyPos.z);

    m_BodyMat = m_BodyRot * m_BodyTrans;

    //Head//
    Math::Matrix tmpMat = DirectX::XMMatrixTranslation(0, 1.25, 0);

    m_Head->GetMat() = tmpMat * m_BodyMat;

    //RightHand//

    tmpMat = DirectX::XMMatrixTranslation(0.45, 0.45, 0);

    m_RightHand->GetMasterMat() = m_RightHand->GetMat() * tmpMat * m_BodyMat;

    //LeftHand//

    tmpMat = DirectX::XMMatrixTranslation(-0.45, 0.45, 0);

    m_LeftHand->GetMasterMat() = m_LeftHand->GetMat() * tmpMat * m_BodyMat;

    //Bow//

    tmpMat = DirectX::XMMatrixTranslation(-0.35, -0.4, 0);

    m_Bow->GetMasterMat() = m_Bow->GetMat() * tmpMat * m_LeftHand->GetMasterMat();

    //Quiver//

    tmpMat = DirectX::XMMatrixTranslation(0.3, 0.5, -0.35);

    m_Quiver->GetMasterMat() = m_Quiver->GetMat() * tmpMat * m_BodyMat;

    //RightFoot//

    tmpMat = DirectX::XMMatrixTranslation(0.38, -0.55, 0);

    m_RightFoot->GetMasterMat() = m_RightFoot->GetMat() * tmpMat * m_BodyMat;

    //LeftFoot//

    tmpMat = DirectX::XMMatrixTranslation(-0.38, -0.55, 0);

    m_LeftFoot->GetMasterMat() = m_LeftFoot->GetMat() * tmpMat * m_BodyMat;
}

void PlayerBase::Move(const float _camAngX, const float _camAngY)
{
    //Move//

    m_MoveFlag = false;

    float Movepow = 0.5f;

    if (GetAsyncKeyState('W') & 0x8000)
    {
        Math::Matrix camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_camAngY));

        m_MoveVec += DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), camMat);

        m_MoveFlag = true;

    }

    if (GetAsyncKeyState('S') & 0x8000)
    {
        Math::Matrix camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_camAngY));

        m_MoveVec += DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, -1), camMat);

        m_MoveFlag = true;

    }

    if (GetAsyncKeyState('A') & 0x8000)
    {
        Math::Matrix camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_camAngY));

        m_MoveVec += DirectX::XMVector3TransformNormal(Math::Vector3(-1, 0, 0), camMat);

        m_MoveFlag = true;
    }

    if (GetAsyncKeyState('D') & 0x8000)
    {
        Math::Matrix camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_camAngY));

        m_MoveVec += DirectX::XMVector3TransformNormal(Math::Vector3(1, 0, 0), camMat);

        m_MoveFlag = true;

    }

    if (MOUSEONCLICK.GetClickKeyFlag() == true)
    {

        ShootingMoveWay(_camAngY);

        Movepow = 0.2f;

        m_RightFoot->Animate(0.04f);

        m_LeftFoot->Animate(0.04f);

    }

    if (m_MoveFlag == true)
    {

        if (m_SoundMoveFlag == true)
        {

            m_SoundMove->InstancePlay();

            m_SoundMoveFlag = false;
        }

        if (m_SoundMove->SoundInstanceIsPlay() == false)
        {
            m_SoundMove->InstancePlay();
        }

        m_MoveVec.Normalize();

        m_MoveVec *= Movepow;

        m_BodyPos += m_MoveVec;

        if (MOUSEONCLICK.GetClickKeyFlag() == false)
        {
            CharactorMoveWay();

            m_RightFoot->Animate(0.05f);

            m_LeftFoot->Animate(0.05f);
        }
        
        if (m_MoveFlag == false)
        {

            if (m_RightFoot->GetAnimateFrame() > 0)
            {

                m_RightFoot->SetAnimateFrame(-0.05);

                m_RightFoot->AnimateProc();

            }

            if (m_RightFoot->GetAnimateFrameBack() > 0)
            {

                m_RightFoot->SetAnimateFrameBack(-0.05);

                m_RightFoot->AnimateProcBack();

            }

            if (m_LeftFoot->GetAnimateFrame() > 0)
            {

                m_LeftFoot->SetAnimateFrame(-0.05);

                m_LeftFoot->AnimateProc();

            }

            if (m_LeftFoot->GetAnimateFrameback() > 0)
            {

                m_LeftFoot->SetAnimateFrameback(-0.05);

                m_LeftFoot->AnimateProcback();

            }

        }

    }
    if (m_MoveFlag == false)
    {

        if (m_RightFoot->GetAnimateFrame() > 0)
        {

            m_RightFoot->SetAnimateFrame(-0.05);

            m_RightFoot->AnimateProc();

        }

        if (m_RightFoot->GetAnimateFrameBack() > 0)
        {

            m_RightFoot->SetAnimateFrameBack(-0.05);

            m_RightFoot->AnimateProcBack();

        }

        if (m_LeftFoot->GetAnimateFrame() > 0)
        {

            m_LeftFoot->SetAnimateFrame(-0.05);

            m_LeftFoot->AnimateProc();

        }

        if (m_LeftFoot->GetAnimateFrameback() > 0)
        {

            m_LeftFoot->SetAnimateFrameback(-0.05);

            m_LeftFoot->AnimateProcback();

        }

    }
}

void PlayerBase::CharactorMoveWay()
{
    Math::Vector3 nowVec;

    Math::Matrix RotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_MoveAngle));

    nowVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), RotMat);

    Math::Vector3 toVec;

    toVec = m_MoveVec;

    nowVec.Normalize();

    toVec.Normalize();

    Math::Vector3 dot;

    dot = DirectX::XMVector3Dot(nowVec, toVec);

    if (dot.x > 1)
    {

        dot.x = 1;

    }
    if (dot.x < -1)
    {

        dot.x = -1;

    }
    float tmpangle = dot.x;

    float angle = DirectX::XMConvertToDegrees(acos(tmpangle));

    if (angle > 0)
    {

        if (angle > 10)
        {

            angle = 10.0f;

        }

        Math::Vector3 cross;

        cross = DirectX::XMVector3Cross(toVec, nowVec);

        cross.Normalize();

        if (cross.y >= 0)
        {

            m_MoveAngle -= angle;

        }
        else
        {

            m_MoveAngle += angle;

        }

    }
}

void PlayerBase::Shoot(const float _camAngX, const float _camAngY)
{
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
   
        m_ShootWaitTime++;

        if(m_ShootSoundFlag == false)
        {
            m_SoundShoot->InstancePlay();

            m_ShootSoundFlag = true;
        }

        m_SoundJump->InstancePlay();

        if (MOUSEONCLICK.GetClickKeyFlag() == false)
        {
            
            MOUSEONCLICK.SetClickKeyFlag(true);

        }
        if (m_ShootWaitTime >= 35)
        {
            m_ShootFlag = true;
        }
    }
    else
    {
        MOUSEONCLICK.SetClickKeyFlag(false);

    }
    if(m_ShootFlag==true&& MOUSEONCLICK.GetClickKeyFlag()==false)
    {
        m_ShootFlag = false;

        m_ShootWaitTime = 0;

        m_SoundArrow->InstancePlay();

        Math::Matrix tmpRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_camAngY + 0.65));

        Math::Matrix tmpRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(_camAngX + 7));

        Math::Matrix PosMat = DirectX::XMMatrixTranslation(m_BodyMat._41 - 0.5, m_BodyMat._42, m_BodyMat._43 + 1);

        Math::Matrix Rotmat = tmpRotX * tmpRotY * PosMat;

        Arrow* newarrow = new Arrow(Rotmat);

        m_Arrow.push_back(newarrow);

        EffectTexture* newarroweffect = new EffectTexture(PosMat);  

        m_ArrowEffect.push_back(newarroweffect);

        m_ShootAnimateFlag = false;

        m_ShootSoundFlag = false;
    }

    ShootAnimate();
   
}

void PlayerBase::ShootAnimate()
{
    if (MOUSEONCLICK.GetClickKeyFlag() == true)
    {
        if(m_RightHand->GetAnimateFrame()<0.9&& m_ShootAnimateFlag==false)
        {
            m_RightHand->SetAnimateFrame(1);

            if(m_RightHand->GetAnimateFrame() > 0.9)
            {

                m_ShootAnimateFlag = true;

            }
           
        }

        if (m_ShootAnimateFlag == true)
        {

            m_ShootAnimateFlag = true;

            m_RightHand->SetAnimateFrame(-0.025f);


        }
        
        m_RightHand->AnimateProc();


        m_LeftHand->SetAnimateFrame(0.1f);

        m_LeftHand->AnimateProc();
    }

    if (MOUSEONCLICK.GetClickKeyFlag() == false)
    {
        m_LeftHand->SetAnimateFrame(-0.05f);

        m_LeftHand->AnimateProc();
    }

}

void PlayerBase::Jump()
{
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {

        if (m_JumpFlag == false && m_Gravity == 0 )
        {
            m_SoundJump->InstancePlay();

            m_JumpFlag = true;

            m_Gravity = 1.0f;

            m_TounchGround = true;

        }

    }
    else
    {
        m_JumpFlag = false;
    }

    m_BodyPos.y += m_Gravity;

    m_Gravity -= 0.05f;

    if (m_Gravity < -1.5)
    {

        m_Gravity = -2;

    }

}

void PlayerBase::ShootingMoveWay(float _camAngY)
{
    Math::Vector3 nowVec;

    Math::Matrix RotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_MoveAngle));

    nowVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), RotMat);

    Math::Vector3 toVec;

    Math::Matrix camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_camAngY));

    toVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), camMat);

    nowVec.Normalize();

    toVec.Normalize();

    Math::Vector3 dot;

    dot = DirectX::XMVector3Dot(nowVec, toVec);

    if (dot.x > 1)
    {

        dot.x = 1;

    }
    if (dot.x < -1)
    {

        dot.x = -1;

    }
    float tmpangle = dot.x;

    float angle = DirectX::XMConvertToDegrees(acos(tmpangle));

    if (angle > 0)
    {

        if (angle > 20)
        {

            angle = 20.0f;

        }

        Math::Vector3 cross;

        cross = DirectX::XMVector3Cross(toVec, nowVec);

        cross.Normalize();

        if (cross.y >= 0)
        {

            m_MoveAngle -= angle;

        }
        else
        {

            m_MoveAngle += angle;

        }

    }
  
}

