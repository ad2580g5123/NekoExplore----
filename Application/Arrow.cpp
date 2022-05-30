#include "Headers.h"
Arrow::Arrow(const Math::Matrix& _initMat)
{

	m_Mat = _initMat;

	m_Gravity = 1.0;

	m_Flag = true;

	m_Radius = 5;

	m_EndCount = 0;
}

bool Arrow::Update()
{

	if (m_EndCount > 120)
	{
		m_Flag = false;
	}

	if(m_Flag==false)return false;

	Math::Matrix tmpMat;

	//tmpMat = DirectX::XMMatrixTranslation(0, m_gravity, 0.5);

	tmpMat = DirectX::XMMatrixTranslation(0,0,2);

	m_Mat = tmpMat*m_Mat;

	m_EndCount++;

	return true;
		
}


void Arrow::Draw()
{

}

Arrow::~Arrow()
{


}

const Math::Matrix& Arrow::GetMat()const
{

	return m_Mat;

}
const bool& Arrow::GetFlag()const
{

	return m_Flag;

}

void Arrow::SetFlag(const bool _flag)
{

	m_Flag = _flag;

}

void Arrow::SetPos(const Math::Vector3 _pos)
{
	m_Mat = DirectX::XMMatrixTranslation(_pos.x,_pos.y,_pos.z);
}

const float& Arrow::GetRadius()const
{

	return m_Radius;

}


