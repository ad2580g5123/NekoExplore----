#pragma once

class Billboard
{
public:
	// ?Šú‰»
	void Init();

	void Update();
	// •`‰æ??
	void Draw();
	// I—¹??
	void Release();

private:
	KdBuffer m_vb; //vertex buffer
	Math::Matrix m_mat;
	KdTexture m_tex;
	int m_animate;
};
