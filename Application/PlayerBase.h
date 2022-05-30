#pragma once //prevent muti include//

//class

class PlayerBase :public Object
{
public:

	PlayerBase();

	~PlayerBase();

	virtual void Update(float _camAngX, float _camAngY);

	void Draw();

	//Getter//

	const Math::Matrix& GetMat()const override;

	const float& GetRadius()const;

	const Math::Vector3& GetPos()const;

	const KdModel& GetModel()const override;

	const Math::Vector3& GetMoveVec()const;

	const Math::Vector3& GetHitPos()const;

	const float& GetrayDis()const;

	const Math::Vector3 GetLookVec(const float _camAngX, const float _camAngY)const;

	//Setter//

	void SetPos(const Math::Vector3 _pos);

	void SetBodyPartsPos();

	//Action//

	void Move(const float _camAngX, const float _camAngY);

	void CharactorMoveWay();

	void ShootingMoveWay(float _camAngY);

	void Shoot(const float _camAngX, const float _camAngY);

	void ShootAnimate();

	void Jump();
private:

protected:
	//Move//

	Math::Vector3 m_MoveVec;

	bool m_MoveFlag;

	float m_MoveAngle;

	//shoot//

	bool m_ShootFlag;

	bool m_ShootAnimateFlag;

	bool m_ShootSoundFlag;

	float m_ShootWaitTime;

	//Jump//

	bool m_JumpFlag;

	float m_Gravity;

	//Radius//

	float m_Radius;

	//Object//

	Head* m_Head = nullptr;

	RightHand* m_RightHand = nullptr;

	LeftHand* m_LeftHand = nullptr;

	RightFoot* m_RightFoot = nullptr;

	LeftFoot* m_LeftFoot = nullptr;

	Bow* m_Bow = nullptr;

	Quiver* m_Quiver = nullptr;

	std::vector<Arrow*> m_Arrow ;

	std::vector<EffectTexture*> m_ArrowEffect;

	//Body//

	KdModel m_BodyModel;

	Math::Matrix m_BodyTrans;

	Math::Matrix m_BodyRot;

	Math::Matrix m_BodyMat;

	Math::Vector3 m_BodyPos;

	//model ray//

	Math::Vector3 m_NormalVec;

	float m_RayDis = 0;

	Math::Vector3 m_HitPos;

	//Sound//

	SoundEffect* m_SoundMove;

	bool m_SoundMoveFlag;

	SoundEffect* m_SoundArrow;

	SoundEffect* m_SoundShoot;

	SoundEffect* m_SoundJump;

	SoundEffect* m_SoundFallDown;

	//Touching Grond//

	bool m_TounchGround;

	//blend//

	ID3D11BlendState* m_BlendAlpha;

	ID3D11BlendState* m_BlendAdd;



};