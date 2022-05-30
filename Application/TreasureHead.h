#pragma once //prevent muti include//

//class
class TreasureHead :public Object
{

public:

	TreasureHead();

	~TreasureHead();

	void Update();

	void Draw();

	void AnimateProc();

	const float& GetAnimateFrame()const;

	void SetAnimateFrame(const float _val);

private:

	KdModel m_Model;

	Math::Matrix m_Mat;

	Math::Matrix m_MasterMat;

	Math::Vector3 m_Pos;

	Math::Matrix m_StartMat;

	Math::Matrix m_EndMat;

	float m_AnimeFrame;
};