#pragma once

class System
{
public:
	static System& GetInstance()
	{
		static System instance;
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
	System()
	{

	};

	bool m_ClickKeyFlag = false;
};
#define SYSTEM System::GetInstance()