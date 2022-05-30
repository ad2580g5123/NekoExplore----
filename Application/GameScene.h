#pragma once
class GameScene :public SceneBase
{
public:

	GameScene();

	void Frame()override;

	void Update()override;

	void Draw()override;

	void DynamicDraw();

	~GameScene()override;

	//Getter//
	int GetScenceMoveNum();

	PlayerGameScene& GetPlayer()const;

	Ground& GetGround()const;

	PushCrystal& GetPushCrystal()const;

	Stairs& GetStair(int _num)const;

	Button& GetButton(int _num)const;

	QuickSand& GetQuickSand()const;

	CameraGameScene& GetCamera()const;

	void SetScenceMoveNum(const int _num);

	void CheckSceneChange();


private:
	//object//

	PlayerGameScene* m_Player = nullptr;

	Sky* m_Sky = nullptr;

	Ground* m_Ground = nullptr;

	QuickSand* m_QuickSand = nullptr;

	Button* m_Button[3];

	Target* m_Target = nullptr;

	PushCrystal* m_PushCrystal = nullptr;

	Stairs* m_Stair[2];

	Treasure* m_Treasure = nullptr;

	//font//

	DirectX::SpriteFont* m_SpriteFont;
	
	//mouse//

	POINT m_BaseMousePos;

	//camera//

	CameraGameScene* m_Camera = nullptr;

	//SoundBgm//

	SoundBgm* m_BgmPlayer;

	//Buffer//
	KdTexture m_SubBuffer;

	//SceneChange//
	float m_SceneAlpha;

	bool m_SceneChangeFlag;

	int m_ScenceMoveNum;

};
