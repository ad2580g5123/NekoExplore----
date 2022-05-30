#pragma once //prevent muti include//

//class
class TreasureBody :public Object
{

public:

	TreasureBody(GameScene* _gamescene);

	~TreasureBody();

	void Update();

	void Draw();

	float GetRadius();

	Math::Vector3 GetPos();

	bool GetAnimateFlag();

private:

	KdModel m_Model;

	Math::Matrix m_Mat;

	Math::Vector3 m_Pos;

	float m_Radius;

	GameScene* m_GameScene = nullptr;

	bool m_AnimateFlag;
};