#pragma once //prevent muti include//

//class
class Object
{
public:

	Object();

	~Object();

	virtual void Draw();

	void Update();

	virtual const KdModel& GetModel()const;

	virtual const Math::Matrix& GetMat()const;

private:
	KdModel m_Model;

	Math::Matrix m_Mat;

};