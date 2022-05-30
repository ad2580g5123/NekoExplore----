#pragma once //prevent muti include//

//class
class CameraGameScene :public CameraBase
{

public:

	CameraGameScene(GameScene* _scene);

	~CameraGameScene();

	void Update()override;

	void Frame()override;

	float CameraPosYFllow()override;

	void CheckCameraChangeWaitTime();
private:

	GameScene* m_Scene = nullptr;
};