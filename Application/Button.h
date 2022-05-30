#pragma once //prevent muti include//

//class
class Button :public Object
{

public:

	Button(const float _x, const float _y, const float _z,const float _anglex, const float _angley);

	~Button();

	void Update();

	void Draw();

	const KdModel& GetModel()const override;

	const Math::Matrix& GetMat()const override;

	const Math::Vector3& GetPos()const;

	const bool& GetFlag()const;

	const bool& GetPushedFlag()const;

	const float& GetRadius() const;

	void SetPushedFlag(const bool _flag);

	void SetPos(const Math::Vector3 _vec);

	void ChangeButton();

private:

	GameScene* m_GameScene;

	bool m_Flag;

	KdModel m_Model;

	Math::Matrix m_Mat;

	Math::Vector3 m_Pos;

	float m_Radius;

	bool m_ButtonPushedFlag;

	SoundEffect* m_ChangeSound;

};