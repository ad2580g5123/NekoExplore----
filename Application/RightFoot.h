#pragma once
class RightFoot
{
public:

	RightFoot();

	~RightFoot();

	void Draw();

	void AnimateProc();

	void AnimateProcBack();

	void Animate(float _aniframe);

	const Math::Matrix& GetMat()const;

	Math::Matrix& GetMasterMat();

	const float& GetAnimateFlag()const;

	const float& GetAnimateFrame()const;

	const float& GetAnimateFrameBack()const;

	void SetAnimateFrame(const float _val);

	void SetAnimateFrameBack(const float _val);

	void SetAnimateFlag(const float _state);

	void AnimateFrameReset();


private:
	float m_AnimateFlag;
	Math::Matrix m_Mat;
	KdModel m_Model;
	Math::Matrix m_StartMat;
	Math::Matrix m_EndMat;
	Math::Matrix m_EndMatBack;
	Math::Matrix m_MasterMat;
	float m_AnimeFrame;
	float m_AnimeFrameBack;
};