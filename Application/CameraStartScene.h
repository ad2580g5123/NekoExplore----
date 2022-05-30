#pragma once //prevent muti include//

//class
class CameraStartScene:public CameraBase
{

public:

	CameraStartScene(StartScene* _scene);

	~CameraStartScene();

	void Update()override;

	void Frame()override;

	float CameraPosYFllow()override;

	void CheckCameraChangeWaitTime();

private:

	StartScene* m_Scene = nullptr;

};