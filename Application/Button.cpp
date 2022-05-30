#include "Headers.h"
Button::Button(const float _x, const float _y, const float _z,const float _anglex, const float _angley)
{

	m_Model.Load("Data/GroundAll/Button/Button.gltf");

	m_Mat = DirectX::XMMatrixTranslation(_x,_y,_z);

	Math::Matrix RotMatx, RotMaty;

	RotMatx = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(_anglex));

	RotMaty = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_angley));

	m_Mat = RotMatx * RotMaty* m_Mat;

	m_Flag = true;

	m_Radius = 1;

	m_ButtonPushedFlag = false;

	m_ChangeSound = SOUNDMANAGER.AddSoundEffect("Data/Sound/Button.WAV");
}

Button::~Button()
{

	m_Model.Release();

}

void Button::Draw()
{

		SHADER.m_standardShader.SetWorldMatrix(m_Mat);

		SHADER.m_standardShader.DrawModel(&m_Model);

}

void Button::Update()
{
	m_Pos = m_Mat.Translation();

	if(GetPushedFlag() == true)//If button has been shoot.
	{
		ChangeButton();
	}
}

const Math::Matrix& Button::GetMat() const
{

	return m_Mat;

}

const KdModel& Button::GetModel() const
{

	return m_Model;

}

const Math::Vector3& Button::GetPos() const
{

	return m_Pos;

}

const bool& Button::GetFlag() const
{
	return m_Flag;
}

const bool& Button::GetPushedFlag() const
{
	return m_ButtonPushedFlag;
}

const float& Button::GetRadius() const
{

	return m_Radius;

}

void Button::SetPushedFlag(const bool _flag)
{
	m_ButtonPushedFlag = _flag;
}

void Button::SetPos(const Math::Vector3 _vec)
{

	m_Mat.Translation() = _vec;

}

void Button::ChangeButton()
{
	m_Model.Release();

	m_Model.Load("Data/GroundAll/Button/Buttonpush.gltf");

	m_ChangeSound->InstancePlay();

	m_Flag = false;
}
