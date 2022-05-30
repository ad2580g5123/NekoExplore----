#pragma once //prevent muti include//

//class
class Treasure :public Object
{

public:

	Treasure(GameScene* _gamescene);

	~Treasure();

	void Update();

	void Draw();

	float GetRadius();

	Math::Vector3 GetPos();

	float GetAnimateWaitTime();
private:

	TreasureBody* m_TreasureBody = nullptr;

	TreasureHead* m_TreasureHead = nullptr;

	float m_AnimateWaitTime;

	SoundEffect* m_Sound;

	bool m_SoundFlag;
};