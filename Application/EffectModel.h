#pragma once
class EffectModel :public Effect
{
public:

	void Update(const Math::Matrix& _posmat)override;

	void Draw()override;

	EffectModel(const Math::Matrix& _posmat, std::string _fileName);

	~EffectModel();

private:

	Math::Matrix m_Mat;

	KdModel m_Model;

};