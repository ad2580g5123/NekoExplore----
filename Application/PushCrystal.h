#pragma once //prevent muti include//

//class
class PushCrystal :public Object
{
public:

	PushCrystal(GameScene* _gamescene);

	~PushCrystal();

	void Draw()override;

	void Update();

	//Getter//

	const Math::Matrix& GetMat()const override;

	const KdModel& GetModel()const override;

	const Math::Vector3& GetPos()const;

	const bool& GetFlag() const;

	const float& GetHp() const;

	const float& GetAlpha() const;

	const float& GetRadius() const;

	//Setter//

	void SetFlag(const bool _flag);

	void SetHp(const float _hp);

	void SetAlpha(const float _alpha);

	void AddPos(const Math::Vector3 _vec);

private:
	GameScene* m_GameScene = nullptr;

	bool m_Flag;

	KdModel m_Model;

	Math::Matrix m_Mat;

	float m_Hp;

	float m_Alpha;

	float m_Radius;

	SoundEffect* m_Sound;

	bool m_SoundFlag;

	float m_AccelAngle;
};