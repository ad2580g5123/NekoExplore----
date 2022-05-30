#pragma once //prevent muti include//

//class
class Sky
{

public:

	Sky(std::string _modelname);

	~Sky();

	void Draw();

private:

	KdModel m_Model;

	Math::Matrix m_Mat;

};