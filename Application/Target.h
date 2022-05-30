#pragma once
class Target
{
public:

	Target();

	~Target();

	void Update();

	void Draw();

private:

	KdTexture m_Tex;

	KdTexture m_TexCenter;

	float m_ScaleNum;

	Math::Matrix m_Mat;

	Math::Matrix m_MatCenter;

	Math::Matrix m_ScaleMat;

	Math::Matrix m_PosMat;
};