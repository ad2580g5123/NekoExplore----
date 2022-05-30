#pragma once

class KdTexture;

// サ?プ?ステート
enum class KdSamplerFilterMode {
	Point,			// ポイ?トフィ?タ
	Linear,			// 線形フィ?タ
	Anisotropic,	// 異方性フィ?タ
};

enum class KdSamplerAddressingMode {
	Wrap,			// ?ップ?ード
	Clamp,			// ク??プ?ード
};

// ブ??ド?ード用定?
enum class KdBlendMode {
	NoBlend,		// ブ??ドをしない
	Alpha,			// 半透明ブ??ド
	Add,				// 加算ブ??ド
	Stencil
};

//=======================================================================================
//
// Direct3Dク?ス
//
//	Direct3D11に必要な変?や、よく行う?作をまとめています。
//
//
//=======================================================================================
class KdDirect3D {
public:

	//==============================================================
	//
	// 取得
	//
	//==============================================================

	// Direct3Dデバイス取得
	ID3D11Device*				GetDev() { return m_pDevice; }

	// Direct3Dデバイスコ?テキスト取得
	ID3D11DeviceContext*		GetDevContext() { return m_pDeviceContext; }

	// SwapChain取得
	IDXGISwapChain*				GetSwapChain() { return m_pGISwapChain; }

	// バックバッファ取得
	std::shared_ptr<KdTexture>	GetBackBuffer() { return m_backBuffer; }

	// Zバッファ取得
	std::shared_ptr<KdTexture>	GetZBuffer() { return m_zBuffer; }

	// ビ?ーポート取得
	void						GetViewport(Math::Viewport& out) const;

	// 1x1 ?テクスチ?取得
	std::shared_ptr<KdTexture>	GetWhiteTex() const { return m_texWhite; }


	//RenderTarget->BackBuffer 
	void                        SetBackBuffer();
	//==============================================================
	//
	// ?期化・解放
	//
	//==============================================================

	// ?期化
	// ・hWnd			… ウィ?ドウのハ?ド?
	// ・w				… X解?度
	// ・h				… Y解?度
	// ・debugDevice	… デバッグ?ード
	// ・errMsg			… (出力)エ?ー?ッセージが入ってくる
	bool Init(HWND hWnd, int w, int h, bool deviceDebug, std::string& errMsg);

	// 解放
	void Release();

	//==============================================================
	//
	// パイプ?イ?ステート作成関?
	//
	//==============================================================

	// 深度ステ?シ?ステート作成
	// ・device				… D3Dデバイス
	// ・zEnable			… 深度テスト有効
	// ・zWriteEnable		… 深度?き?み有効
	ID3D11DepthStencilState* CreateDepthStencilState(bool zEnable, bool zWriteEnable) const;

	// ?スタ?イザーステート作成
	// ・device				… D3Dデバイス
	// ・cullMode			… カ??グ?ード
	// ・fillMode			… 三角形の描画?ード
	// ・depthClipEnable	… Zク?ッピ?グを有効にする
	// ・scissorEnable		… 切り抜き範囲を有効にする
	ID3D11RasterizerState* CreateRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool depthClipEnable, bool scissorEnable) const;

	// サ?プ?ーステート作成
	// ・device				… D3Dデバイス
	// ・filterType			… 0:補間なし 1:線形フィ?タ 2:異方性フィ?タ
	// ・maxAnisotropy		… 異方性フィ?タ?の最大値　2, 4, 6, 8, 10, 12, 14, 16 のいずれか
	// ・addressingMode		… テクスチ?アド?ッシ?グ?ード 0:Wrap 1:Clamp
	// ・comparisonModel	… 比較?ードON　シ?ドウマッピ?グなどで使用する
	ID3D11SamplerState* CreateSamplerState(KdSamplerFilterMode filterType, UINT maxAnisotropy, KdSamplerAddressingMode addressingMode, bool comparisonModel) const;

	// ブ??ドステート作成
	// ・device				… D3Dデバイス
	// ・mode				… ?成?ード
	ID3D11BlendState* CreateBlendState(KdBlendMode mode) const;


	void SetBlendState(KdBlendMode mode);
	//==============================================================

	// 頂点を描画する簡易的な関?
	// ・topology		… 頂点をどのような形状で描画するか　D3D_PRIMITIVE_TOPOLOGYマク?を使用
	// ・vertexCount	… 頂点?
	// ・pVertexStream	… 頂点配列の先頭アド?ス
	// ・stride			… １頂点のバイトサイズ
	void DrawVertices(D3D_PRIMITIVE_TOPOLOGY topology, int vertexCount, const void* pVertexStream, UINT stride);

	//==============================================================

	// 
	~KdDirect3D() {
		Release();
	}

private:

	ID3D11Device*				m_pDevice = nullptr;			// Direct3D11の?心になるク?ス。全体の管?とバッファ、シェーダ、テクスチ?などの?ソース作成などを行う。D3D9とは違って、このク?スは描画関係の??バ関?を?たない。
	ID3D11DeviceContext*		m_pDeviceContext = nullptr;		// 描画??を行うク?ス。
																// 内?的には、??ダ??グコマ?ドと呼ばれるバイナ?データを作成し、GPUに?る。GPUが??ダ??グコマ?ドを解析することで実際の描画??が行われる。

	IDXGIAdapter*				m_pGIAdapter = nullptr;			// ディスプ?イ サブシステ?(1つまたは複?のGPU、DAC、およびビデオ ???ー)。
	IDXGIFactory*				m_pGIFactory = nullptr;			// フ?スク?ー?切り替えなどで使用。
	IDXGISwapChain*				m_pGISwapChain = nullptr;		// ウイ?ドウへの表示やダブ?バッファ??グなどを行うク?ス。マ?チサ?プ??グ、?フ?ッシ??ートなどの設定もできるみたい。

	// バッファ
	std::shared_ptr<KdTexture>	m_backBuffer;					// バックバッファ
	std::shared_ptr<KdTexture>	m_zBuffer;						// Zバッファ

	// DrawVertices用 頂点バッファ
	KdBuffer					m_tempFixedVertexBuffer[10];	// 固定長 頂点バッファ
	KdBuffer					m_tempVertexBuffer;				// 可変長 頂点バッファ

	//------------------------
	// 便?テクスチ?
	//------------------------
	// 1x1 ?テクスチ?
	std::shared_ptr<KdTexture>	m_texWhite;


//-------------------------------
// シ?グ?ト?
//-------------------------------
private:

	KdDirect3D() {
	}

public:
	static KdDirect3D &GetInstance() {
		static KdDirect3D instance;
		return instance;
	}
};

// 簡単にアクセスできるようにするためのマク?
#define D3D KdDirect3D::GetInstance()
