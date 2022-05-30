#pragma once //prevent muti include//

//class
class Crystal :public Object
{

public:

	Crystal(const Math::Vector3 _pos,const int _hp);

	~Crystal();

	void Draw()override;

	void Update();

	const Math::Matrix& GetMat()const override;

	const KdModel& GetModel()const override;

	const Math::Vector3& GetPos()const;

	const bool& GetFlag() const;

	const float& GetHp() const;

	const float& GetAlpha() const;

	const float& GetRadius() const;

	void SetFlag(const bool _flag);

	void SetHp(const float _hp);

	void SetAlpha(const float _alpha);

	void SetPos(const Math::Vector3 _vec);

	void SoundPlay();

private:

	bool m_Flag;

	bool m_CheckFlag;

	KdModel m_Model;

	Math::Matrix m_Mat;

	float m_Hp;

	float m_Alpha;

	Math::Vector3 m_Pos;

	float m_Radius;

	SoundEffect* m_Sound;

};