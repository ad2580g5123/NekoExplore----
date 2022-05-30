#pragma once //prevent muti include//

//class
class Stairs :public Object
{
public:

	 Stairs(Math::Vector3 _startVec, Math::Vector3 _endVec);

	~Stairs();

	void Update();

	void Draw()override;

	const KdModel& GetModel()const override;

	const Math::Matrix& GetMat()const override;

	const bool& GetFlag() const;

	const Math::Vector3& GetMoveScale()const;

	void SetFlag(const bool _flag);

private:

	KdModel m_Model;

	Math::Matrix m_Mat;

	float m_WaitTime;

	int m_SinAngle;

	Math::Vector3 m_MoveScale;

	bool m_Flag;

	Math::Vector3 m_Pos;

	Math::Vector3 m_StartPos;

	Math::Vector3 m_EndPos;

	float m_Speed;

	float m_SlowRate;

	bool m_AccelFlag;

	bool m_FirstTimeChangeFlag;

	SoundEffect* m_SoundStairMove;

};