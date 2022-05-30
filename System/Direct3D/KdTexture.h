#pragma once

//====================================================
//
// テクスチ?ク?ス
//
//====================================================
class KdTexture
{
public:

	//====================================================
	//
	// 取得
	//
	//====================================================

	// 画?のアスペクト比取得
	float								GetAspectRatio() const { return (float)m_desc.Width / m_desc.Height; }
	// 画?の?を取得
	UINT								GetWidth() const { return m_desc.Width; }
	// 画?の?さを取得
	UINT								GetHeight() const { return m_desc.Height; }
	// 画?の全情報を取得
	const D3D11_TEXTURE2D_DESC&			GetInfo() const { return m_desc; }
	// ファイ?パス取得(Load?のみ)
	const std::string&					GetFilepath() const { return m_filepath; }


	// 画??ソースを取得
	ID3D11Texture2D*					GetResource() const;

	// シェーダ?ソースビ?ー取得
	ID3D11ShaderResourceView*			GetSRView() const { return m_srv; }
	// シェーダ?ソースビ?ーのアド?ス取得
	ID3D11ShaderResourceView* const*	GetSRViewAddress() const { return &m_srv; }

	// ??ダーターゲットビ?ー取得
	ID3D11RenderTargetView*				GetRTView() const { return m_rtv; }
	// ??ダーターゲットビ?ーのアド?ス取得
	ID3D11RenderTargetView* const*		GetRTViewAddress() const { return &m_rtv; }

	// 深度ステ?シ?ビ?ー取得
	ID3D11DepthStencilView*				GetDSView() const { return m_dsv; }

	//====================================================
	//
	// 画?ファイ?からテクスチ?作成
	//
	//====================================================

	// 画?ファイ?を読み?む
	// ・filename		… 画?ファイ?名
	// ・renderTarget	… ??ダーターゲットビ?ーを生成する(??ダーターゲットにする)
	// ・depthStencil	… 深度ステ?シ?ビ?ーを生成する(Zバッファにする)
	// ・generateMipmap	… ミップマップ生成する？
	bool Load(const std::string& filename, bool renderTarget = false, bool depthStencil = false, bool generateMipmap = false);

	//====================================================
	//
	// テクスチ?作成
	//
	//====================================================

	// ?ソースから作成
	// ・pTexture2D	… 画??ソース
	// 戻り値：true … 成功
	bool Create(ID3D11Texture2D* pTexture2D);

	// desc情報からテクスチ??ソースを作成する
	// ・desc		… 作成するテクスチ??ソースの情報
	// ・fillData	… バッファに?き?むデータ　nullptrだと?き?みなし
	// 戻り値：true … 成功
	bool Create(const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// 通常テクスチ?として作成
	// ※テクスチ??ソースを作成し、ShaderResourceViewのみを作成します
	// ・w			… 画?の?(ピクセ?)
	// ・h			… 画?の?さ(ピクセ?)
	// ・format		… 画?の形式　DXGI_FORMATを使用
	// ・arrayCnt	… 「テクスチ?配列」を使用する場?、その?。1で通常の1?テクスチ?
	// ・fillData	… バッファに?き?むデータ　nullptrだと?き?みなし
	// 戻り値：true … 成功
	bool Create(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// ??ダーターゲットテクスチ?として作成
	// ※テクスチ??ソースを作成し、RenderTargetViewとShaderResourceViewの2種類を作成します
	// ・w			… 画?の?(ピクセ?)
	// ・h			… 画?の?さ(ピクセ?)
	// ・format		… 画?の形式　DXGI_FORMATを使用
	// ・arrayCnt	… 「テクスチ?配列」を使用する場?、その?。1で通常の1?テクスチ?
	// ・fillData	… バッファに?き?むデータ　nullptrだと?き?みなし
	// 戻り値：true … 成功
	bool CreateRenderTarget(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// Zバッファテクスチ?として作成
	// ※テクスチ??ソースを作成し、DepthStencilViewとShaderResourceViewの2種類を作成します
	// ・w			… 画?の?(ピクセ?)
	// ・h			… 画?の?さ(ピクセ?)
	// ・format		… 画?の形式　DXGI_FORMATを使用　32bit：DXGI_FORMAT_R32_TYPELESS  ステ?シ?付き：DXGI_FORMAT_R24G8_TYPELESS
	// ・arrayCnt	… 「テクスチ?配列」を使用する場?、その?。1で通常の1?テクスチ?
	// ・fillData	… バッファに?き?むデータ　nullptrだと?き?みなし
	// 戻り値：true … 成功
	bool CreateDepth(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R32_TYPELESS, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	void SetRenderTarget();
	//====================================================
	//
	// ビ?ーから作成
	//
	//====================================================
	// ShaderResourceViewをセットする
	void SetSRView(ID3D11ShaderResourceView* srv);

	// 
	KdTexture() {}

	//====================================================
	// 解放
	//====================================================
	void Release();

	// 
	~KdTexture()
	{
		Release();
	}

private:

	// シェーダ?ソースビ?ー(読み取り用)
	ID3D11ShaderResourceView*	m_srv = nullptr;
	// ??ダーターゲットビ?ー(?き?み用)
	ID3D11RenderTargetView*		m_rtv = nullptr;
	// 深度ステ?シ?ビ?ー(Zバッファ用)
	ID3D11DepthStencilView*		m_dsv = nullptr;

	// 画?情報
	D3D11_TEXTURE2D_DESC		m_desc = {};

	// 画?ファイ?名(Load?専用)
	std::string					m_filepath;

private:
	// コピー禁止用
	KdTexture(const KdTexture& src) = delete;
	void operator=(const KdTexture& src) = delete;
};
