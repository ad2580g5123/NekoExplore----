#pragma once

class MouseOnClick
{
public:
	static MouseOnClick& GetInstance()
	{
		static MouseOnClick instance;
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
	MouseOnClick()
	{

	};

	bool m_ClickKeyFlag = false;
};
#define MOUSEONCLICK System::GetInstance()