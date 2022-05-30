#pragma once
class EffectTexture :public Effect
{
public:

	void Update(const Math::Matrix& _posmat)override;

	void Draw()override;

	EffectTexture(const Math::Matrix& _posmat);

	~EffectTexture();

private:

	Math::Matrix m_Mat[10];

	KdTexture m_Tex;

	KdBuffer m_Vb; //vertex buffer
};