#pragma once

#include "EffectShader/KdEffectShader.h"
#include "StandardShader/KdStandardShader.h"
#include "SpriteShader/KdSpriteShader.h"

//==========================================================
//
// シェーダ関係をまとめたク?ス
//
//==========================================================
class KdShaderManager
{
public:

	//==============================================================
	//
	// ?期化・解放
	//
	//==============================================================

	// ?期化
	void Init();

	// 解放
	void Release();

	//==========================
	//
	// シェーダ
	//
	//==========================
	KdStandardShader		m_standardShader;		// 3D?デ?描画シェーダ
	KdEffectShader			m_effectShader;			// エフェクト描画シェーダ
	KdSpriteShader			m_spriteShader;			// 2Dテクスチ?描画シェーダ


	//==========================
	//
	// カ??関係
	//
	//==========================

	// カ??定?バッファ用構造体
	struct cbCamera
	{
		Math::Matrix		mV;			// ビ?ー行列
		Math::Matrix		mP;			// 射影行列
		Math::Vector3		CamPos;		// カ???ー?ド座標

		int					DistanceFogEnable = 0;			// ?離フォグ有効
		Math::Vector3		DistanceFogColor = { 1, 1, 1 };	// ?離フォグ色
		float				DistanceFogDensity = 0.001f;	// ?離フォグ減?率
	};

	// カ??定?バッファ
	KdConstantBuffer<cbCamera>	m_cb7_Camera;


	//==========================
	//
	// ?イト関係
	//
	//==========================

	struct PointLight
	{
		Math::Vector3		color = { 3,3,3 };  // 光の色
		float				radius = 0;		//効果半径
	//16バイト区切り------------------------------
		Math::Vector3		pos = {};		//光の位置
		float					tmp4;
	//16バイト区切り------------------------------
	};

	// ?イト定?バッファ用構造体
	struct cbLight
	{
		// 環境光
		Math::Vector3		AmbientLight = {0.0f, 0.0f, 0.0f};
		float					tmp;
	//16バイト区切り------------------------------
		// 平行光
		Math::Vector3		DL_Dir = {0,-1,0};    // 光の方向
		float					tmp2;
	//16バイト区切り------------------------------
		Math::Vector3		DL_Color = {1,1,1};  // 光の色
		float					tmp3;
	//16バイト区切り------------------------------
		PointLight			PL[100];
	//16バイト区切り------------------------------
		int					PL_Num = 0;
		float					tmp4[3];
	//16バイト区切り------------------------------
	};

	// ?イト定?バッファ
	KdConstantBuffer<cbLight>		m_cb8_Light;

	void AddPointLight(const Math::Vector3& _color, const Math::Vector3& _pos, const float _radius)
	{
		int index = m_cb8_Light.Work().PL_Num;

		//最?100個まで
		if (index < 100)
		{
			m_cb8_Light.Work().PL[index].color = _color;
			m_cb8_Light.Work().PL[index].pos = _pos;
			m_cb8_Light.Work().PL[index].radius = _radius;

			m_cb8_Light.Work().PL_Num++;
		}
	}

	//==========================
	//
	// その他
	//
	//==========================





//-------------------------------
// シ?グ?ト?
//-------------------------------
private:

	KdShaderManager() {}

public:
	static KdShaderManager &GetInstance() {
		static KdShaderManager instance;
		return instance;
	}
};

#define SHADER KdShaderManager::GetInstance()
