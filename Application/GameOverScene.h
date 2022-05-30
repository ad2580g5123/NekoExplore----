#pragma once
class GameOverScene :public SceneBase
{
public:

	GameOverScene();

	// •`‰æ??

	void Draw()override;

	void DynamicDraw();

	void Update()override;

	void Frame()override;

	~GameOverScene()override;

private:
	//KdBuffer m_vb; //vertex buffer
	//Math::Matrix m_mat;

	KdTexture m_Tex;

	Math::Matrix m_Mat;

	float BackX;

	KdTexture m_TitleTex;

	Math::Matrix m_TitleMat;

	SoundBgm* m_BgmPlayer;

	SoundEffect* m_SoundClick;

	KdTexture m_SubBuffer;

	float m_SceneAlpha;

	bool m_SceneChangeFlag;
};