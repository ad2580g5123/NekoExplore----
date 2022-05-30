#pragma once
class TitleScene :public SceneBase
{
public:

	TitleScene();

	// •`‰æ??

	void Draw()override;

	void DynamicDraw();

	void Update()override;

	void Frame()override;

	~TitleScene()override;

private:

	KdTexture m_Tex;

	Math::Matrix m_Mat;

	float BackX;

	KdTexture m_TitleTex;

	Math::Matrix m_TitleMat;

	KdTexture m_EnterTex;

	Math::Matrix m_EnterMat;

	SoundBgm* m_BgmPlayer;

	SoundEffect* m_SoundClick;

	KdTexture m_SubBuffer;

	float m_SceneAlpha;

	bool m_SceneChangeFlag;
};