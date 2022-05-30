#pragma once
class Arrow
{
public:

	Arrow(const Math::Matrix& _initMat);

	~Arrow();

	bool Update();

	void Draw();

	const Math::Matrix& GetMat()const;

	const bool& GetFlag()const;

	const float& GetRadius()const;

	void SetFlag(const bool _flag);

	void SetPos(const Math::Vector3 _pos);

private:

	bool m_Flag;

	Math::Matrix m_Mat;

	float m_Gravity;

	float m_Radius;

	float m_EndCount;

	//blend//

	ID3D11BlendState* m_BlendAlpha;

	ID3D11BlendState* m_BlendAdd;

};
