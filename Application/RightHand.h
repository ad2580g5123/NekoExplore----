#pragma once
class RightHand
{
public:

	RightHand();

	~RightHand();

	void Draw();

	void AnimateProc();

	const Math::Matrix& GetMat()const;

	Math::Matrix& GetMasterMat();

	const float& GetAnimateFrame()const;

	void SetAnimateFrame(const float _val);

private:

	Math::Matrix m_Mat;

	KdModel m_Model;

	Math::Matrix m_StartMat;

	Math::Matrix m_EndMat;

	Math::Matrix m_MasterMat;

	float m_AnimeFrame;

};