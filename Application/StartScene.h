#pragma once
class StartScene :public SceneBase
{
public:

	StartScene();

	void Frame()override;

	void Update()override;

	void Draw()override;

	void DynamicDraw();

	~StartScene()override;

	//Getter//
	int GetScenceMoveNum();

	PlayerStartScene& GetPlayer()const;

	Ground& GetGround()const;

	Door& GetDoor()const;

	CameraStartScene& GetStartSceneCamera()const;

	void SetScenceMoveNum(const int _num);

	void SetSceneChangeFlag(const bool _val);


private:
	//object//

	PlayerStartScene* m_Player = nullptr;

	Sky* m_Sky = nullptr;

	Ground* m_Ground = nullptr;

	Door* m_Door = nullptr;

	Target* m_Target = nullptr;

	EffectTexture* m_ShootEffect = nullptr;

	std::vector<Arrow*> m_ArrowCollection;

	//font//

	DirectX::SpriteFont* m_SpriteFont;

	//camera//

	CameraStartScene* m_Camera = nullptr;

	//SoundBgm//

	SoundBgm* m_BgmPlayer;

	//Buffer//
	KdTexture m_SubBuffer;

	//SceneChange//
	float m_SceneAlpha;

	bool m_SceneChangeFlag;

	int m_ScenceMoveNum;
};
