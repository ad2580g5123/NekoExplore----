#pragma once //prevent muti include//

//class
class Door :public Object
{

public:

	Door(const float _x, const float _y, const float _z);

	~Door();

	void Update();

	void Draw();

	const KdModel& GetModel()const override;

	const Math::Matrix& GetMat()const override;

	const float& GetRadius() const;

	void SetPos(const Math::Vector3 _vec);


private:

	KdModel m_Model;

	Math::Matrix m_Mat;

	float m_Radius;

	Math::Vector2 m_UvOffSet;

	SoundEffect* m_Sound;
};