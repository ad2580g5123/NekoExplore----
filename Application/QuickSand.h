#pragma once //prevent muti include//

//class
class QuickSand :public Object
{
public:

	QuickSand(GameScene* _scene);

	~QuickSand();

	void Update();

	void Draw()override;

	const KdModel& GetModel()const override;

	const Math::Matrix& GetMat()const override;

	const float& GetAlpha() const;

	void SetFlag(const bool _flag);

	void SetAlpha(const float _alpha);

	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, Math::Vector3& _normalVec, float& _dis) const;

private:

	KdModel m_Model;

	Math::Matrix m_Mat;

	Math::Vector2 m_UvOffSet;

	float m_Alpha;

	float m_Flag;

	GameScene* m_Scene = nullptr;
};