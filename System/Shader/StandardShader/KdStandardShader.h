#pragma once

//============================================================
//
// 基本シェーダ
//
//============================================================
class KdStandardShader
{
public:

	//================================================
	// 設定・取得
	//================================================

	// ?ー?ド行列セット
	void SetWorldMatrix(const Math::Matrix& m)
	{
//		m_cb0.Work().mW = m;
		m_mTransform = m;
	}
	void SetWorldMatrixMw(const Math::Matrix& m)
	{
		m_cb0.Work().mW = m;
	}

	// UVタイ??グ設定
	void SetUVTiling(const Math::Vector2& tiling)
	{
		m_cb0.Work().UVTiling = tiling;
	}
	// UVオフセット設定
	void SetUVOffset(const Math::Vector2& offset)
	{
		m_cb0.Work().UVOffset = offset;
	}

	// ?イト有効/無効
	void SetLightEnable(bool enable)
	{
		m_cb0.Work().LightEnable = enable;
	}

	// ア?ファテストの?値設定
	// ・alpha	… この値以下のア?ファ値のピクセ?は描画されなくなる
	void SetAlphaTestThreshold(float alpha)
	{
		m_cb0.Work().AlphaTestThreshold = alpha;
	}

	//---------------------
	// 材質パ??ータ設定
	//---------------------

	// 基本色設定
	void SetBaseColor(const Math::Vector4& color)
	{
		m_cb1_Material.Work().BaseColor = color;
	}

	// 自己発光色設定
	void SetEmissive(const Math::Vector3& color)
	{
		m_cb1_Material.Work().Emissive = color;
	}

	// 粗さの設定
	void SetRoughness(float roughness)
	{
		m_cb1_Material.Work().Roughness = roughness;
	}

	// 金属度の設定
	void SetMetallic(float metallic)
	{
		m_cb1_Material.Work().Metallic = metallic;
	}


	// Set系でセットしたデータを、実際に定?バッファへ?き?む
	void WriteToCB()
	{
		m_cb0.Write();
		m_cb1_Material.Write();
	}


	//================================================
	// 描画
	//================================================

	// このシェーダをデバイスへセット
	void SetToDevice();

	// ?ッシ?描画
	// ・mesh			… 描画する?ッシ?
	// ・materials		… 使用する材質配列
	void DrawModel(const KdModel* model,  const float _alpha=1.0f,const std::vector<Math::Matrix>* nodeTransforms = nullptr);

	//================================================
	// ?期化・解放
	//================================================

	// ?期化
	bool Init();
	// 解放
	void Release();
	// 
	~KdStandardShader()
	{
		Release();
	}


private:

	// 3D?デ?用シェーダ
	ID3D11VertexShader*	m_VS = nullptr;				// 頂点シェーダー
	ID3D11InputLayout*	m_inputLayout = nullptr;	// 頂点入力?イアウト

	ID3D11PixelShader*	m_PS = nullptr;				// ピクセ?シェーダー

	// 行列保?用
	Math::Matrix		m_mTransform;

	// 定?バッファ
	//  ※定?バッファは、パッキ?グ規則というものを厳守しなければならない
	//  <パッキ?グ規則> 参考：https://docs.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-packing-rules
	//  ・構造体のサイズは16バイトの倍?にする。
	//  ・各?目(変?)は、16バイト境界をまたぐような場?、?のベクト?に配置される。

	// 定?バッファ(オブジェクト単位更新)
	struct cbObject
	{
		Math::Matrix		mW;		// ?ー?ド行列　行列は16バイトx4バイトの64バイトなのでピッタ?。

		// UV?作
		Math::Vector2		UVOffset = { 0,0 };
		Math::Vector2		UVTiling = { 1,1 };

		// ?イト有効
		int					LightEnable = 1;
		// ア?ファテストの?値
		float				AlphaTestThreshold = 0;

		float tmp[2];
	};
	KdConstantBuffer<cbObject>	m_cb0;

	// 定?バッファ(マテ?ア?単位更新)
	struct cb {
		Math::Vector4	BaseColor;
		Math::Vector3	Emissive;
		float			Metallic;
		float			Roughness;

		float			tmp[3];
	};
	KdConstantBuffer<cb>	m_cb1_Material;

};


