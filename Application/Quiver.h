#pragma once
class Quiver
{
public:

	Quiver();

	~Quiver();

	void Draw();

	const Math::Matrix& GetMat()const;

	Math::Matrix& GetMasterMat();

private:

	Math::Matrix m_Mat;

	Math::Matrix m_MasterMat;

	KdModel m_Model;

};