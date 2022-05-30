#pragma once //prevent muti include//

//class
class CameraBase
{

public:

	CameraBase();

	~CameraBase();

	virtual void Update();

	virtual void Frame();

	float GetCamreaAngleX();

	float GetCamreaAngleY();

	void SetCameraAngleX(float _xangle);

	void SetCameraAngleY(float _yangle);

	void SetCameraWaitTime(float _time);

	void CameraLimit();

	void AddCameraZ(float _num);

	void ShootCameraChangeReturn();

	virtual float CameraPosYFllow();
private:
protected:

	float m_RotX;

	float m_RotY;

	float m_WaitTime;

	Math::Vector3 m_Pos;

	Math::Vector3 m_Look;

	bool m_CameraChangeFlag;

	float m_CameraPosZ;
};