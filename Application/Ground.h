#pragma once //prevent muti include//

//class
class Ground :public Object
{
public:

	Ground(std::string _modelname);

	~Ground();

	void Draw()override;

	const KdModel& GetModel()const override;

	const Math::Matrix& GetMat()const override;

	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, Math::Vector3& _normalVec, float& _dis) const;

private:

	KdModel m_Model;

	Math::Matrix m_Mat;

};