#pragma once //prevent muti include//

//class
class StartScene;
class PlayerStartScene :public PlayerBase
{
public:

	PlayerStartScene(StartScene* _Scene, float _camAngX, float _camAngY,Math::Vector3 _pos);

	~PlayerStartScene();

	void Update(float _camAngY, float _camAngX)override;

	void CheckGround();

	void CheckArrow();

	void CheckDoor();

	void Mouse();

private:

	//Object//

	StartScene* m_StartScene = nullptr;

	//mouse//

	POINT m_BaseMousePos;

};