#pragma once

class Billboard
{
public:
	// ?����
	void Init();

	void Update();
	// �`��??
	void Draw();
	// �I��??
	void Release();

private:
	KdBuffer m_vb; //vertex buffer
	Math::Matrix m_mat;
	KdTexture m_tex;
	int m_animate;
};
