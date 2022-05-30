#pragma once

class ShootingFlag
{
public:
	static ShootingFlag& GetInstance()
	{
		static ShootingFlag instance;
		return instance;
	};
	bool GetClickKeyFlag()
	{
		return m_ClickKeyFlag;
	}
	void SetClickKeyFlag(const bool _value)
	{
		m_ClickKeyFlag = _value;
	}
private:
	ShootingFlag()
	{

	};

	bool m_ClickKeyFlag = true;
};
#define SHOOTINGFLAG System::GetInstance()