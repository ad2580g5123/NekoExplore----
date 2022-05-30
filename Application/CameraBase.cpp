#include "Headers.h"

CameraBase::CameraBase()
{
    //Camera//

    m_RotY = 0;

    m_RotX = 0;

    m_WaitTime = 300;

    m_Pos = {};

    m_CameraPosZ = 0;
}

void CameraBase::Update()
{
}

void CameraBase::Frame()
{
}

float CameraBase::GetCamreaAngleX()
{
    return m_RotX;
}

float CameraBase::GetCamreaAngleY()
{
    return m_RotY;
}

void CameraBase::SetCameraAngleX(float _xangle)
{
    m_RotX += _xangle;
}

void CameraBase::SetCameraAngleY(float _yangle)
{
    m_RotY += _yangle;
}

void CameraBase::SetCameraWaitTime(float _time)
{
    m_WaitTime += _time;
}

void CameraBase::CameraLimit()
{
    if (m_RotY > 360)
    {
        m_RotY = 0;
    }
    if (m_RotY < 0)
    {
        m_RotY = 360.0f;
    }
    if (m_RotX < -20.0f)
    {
        m_RotX = -20.0f;
    }
    if (m_RotX > 45.0f)
    {
        m_RotX = 45.0f;
    }
}

void CameraBase::AddCameraZ(float _num)
{
        m_CameraPosZ += _num;
}

void CameraBase::ShootCameraChangeReturn()
{
    

    if (MOUSEONCLICK.GetClickKeyFlag() == true)
    {
        AddCameraZ(0.1);
    }else
    {
        AddCameraZ(-0.6);
    }

    if (m_CameraPosZ > 3)
    {

        m_CameraPosZ = 3;

    }

    if (m_CameraPosZ < 0)
    {

        m_CameraPosZ = 0;

    }
}

float CameraBase::CameraPosYFllow()
{
    return 0;
}

