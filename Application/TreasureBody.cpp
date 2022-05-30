#include "Headers.h"

TreasureBody::TreasureBody(GameScene* _gamescene)
{

	m_Model.Load("Data/GroundAll/Treasure/TreasureBoxBody.gltf");

	m_Mat = DirectX::XMMatrixTranslation(-673,-128,451);

	m_Radius = 6;

	m_GameScene = _gamescene;

	m_AnimateFlag = false;
}

TreasureBody::~TreasureBody()
{
	m_Model.Release();
}

void TreasureBody::Update()
{
	PlayerGameScene& player = m_GameScene->GetPlayer();

	m_Pos = m_Mat.Translation();

	Math::Vector3 targetVec = m_Pos - player.GetPos();

	float dis = targetVec.Length();

	if (dis < GetRadius() + player.GetRadius())
	{

		float pushPow = (GetRadius() + player.GetRadius()) - dis;

		targetVec.y = 0;

		targetVec.Normalize();

		targetVec *= pushPow;

		
		player.SetPos(player.GetPos() - targetVec);

		m_AnimateFlag = true;
	}
}

void TreasureBody::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(&m_Model);
}

float TreasureBody::GetRadius()
{
	return m_Radius;
}

Math::Vector3 TreasureBody::GetPos()
{
	return m_Pos;
}

bool TreasureBody::GetAnimateFlag()
{
	return m_AnimateFlag;
}
