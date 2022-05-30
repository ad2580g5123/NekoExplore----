#pragma once
class Head
{
public:

	Head();

	~Head();

	void Draw();

	Math::Matrix& GetMat();

private:

	Math::Matrix m_Mat;

	KdModel m_Model;

};