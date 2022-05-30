#pragma once //prevent muti include//

//class
class GameScene;

class PlayerGameScene :public PlayerBase
{
public:

	PlayerGameScene(GameScene* _gameScene, float _camAngX, float _camAngY,Math::Vector3 _pos);

	~PlayerGameScene();

	void Update(float _camAngY, float _camAngX)override;

	//Getter//

	const float& GetCount()const;

	const bool& GetPlayerDeathFlag()const;

	const float& GetPlayerDeathTimeCount()const;
	
	const float& GetMovePower()const;

	const float& GetGroundDis()const;

	const float& GetStairDis()const;

	void CheckGround();

	void CheckButton();

	void CheckArrow();

	void CheckDeathTime();

	void Mouse();


private:
	//Object//

	GameScene* m_GameScene = nullptr;

	//Death//

	float m_DeathTimeCount;

	bool m_PlayerDeathFlag;

	float m_MovePower;

	//RayDis
	float m_GroundDis;

	float m_StairsDis;

	//mouse//

	POINT m_BaseMousePos;
};