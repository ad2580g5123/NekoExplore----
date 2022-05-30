#include "System/KdSystem.h"

void KdDirect3D::GetViewport(Math::Viewport & out) const
{
	UINT numVPs = 1;
	D3D11_VIEWPORT vp;
	m_pDeviceContext->RSGetViewports(&numVPs, &vp);
	out = vp;
}

void KdDirect3D::SetBackBuffer()
{
	m_pDeviceContext->OMSetRenderTargets(1, m_backBuffer->GetRTViewAddress(), m_zBuffer->GetDSView());
}

bool KdDirect3D::Init(HWND hWnd, int w, int h, bool deviceDebug, std::string& errMsg)
{
	HRESULT hr;

	//=====================================================
	// ファクト?ー作成(ビデオ グ?フィックの設定の列?や指定に使用されるオブジェクト)
	//=====================================================
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&m_pGIFactory));
	if (FAILED(hr)) {
		errMsg = "ファクト?ー作成失敗";

		Release();
		return false;
	}

	//=====================================================
	//デバイス生成(主に?ソース作成?に使用するオブジェクト)
	//=====================================================
	UINT creationFlags = 0;

	if (deviceDebug) {
		// Direct3Dのデバッグを有効にする(すごく重いが細かいエ?ーがわかる)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}

	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_1,	// Direct3D 11.1  ShaderModel 5
		D3D_FEATURE_LEVEL_11_0,	// Direct3D 11    ShaderModel 5
		D3D_FEATURE_LEVEL_10_1,	// Direct3D 10.1  ShaderModel 4
		D3D_FEATURE_LEVEL_10_0,	// Direct3D 10.0  ShaderModel 4
		D3D_FEATURE_LEVEL_9_3,	// Direct3D 9.3   ShaderModel 3
		D3D_FEATURE_LEVEL_9_2,	// Direct3D 9.2   ShaderModel 3
		D3D_FEATURE_LEVEL_9_1,	// Direct3D 9.1   ShaderModel 3
	};

	// デバイスとでデバイスコ?テキストを作成
	D3D_FEATURE_LEVEL futureLevel;
	hr = D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				creationFlags,
				featureLevels,
				_countof(featureLevels),
				D3D11_SDK_VERSION,
				&m_pDevice,
				&futureLevel,
				&m_pDeviceContext);
	if FAILED( hr )
	{
		errMsg = "Direct3D11デバイス作成失敗";

		Release();
		return false;
	}

	//=====================================================
	// ス?ップチェイ?作成(フ??トバッファに表示可能なバックバッファを?つもの)
	//=====================================================
	DXGI_SWAP_CHAIN_DESC DXGISwapChainDesc = {};		// ス?ップチェー?の設定データ
	DXGISwapChainDesc.BufferDesc.Width = w;
	DXGISwapChainDesc.BufferDesc.Height = h;
	DXGISwapChainDesc.BufferDesc.RefreshRate.Numerator  = 0;
	DXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	DXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	DXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;// DXGI_MODE_SCALING_CENTERED;	// DXGI_MODE_SCALING_UNSPECIFIED
	DXGISwapChainDesc.SampleDesc.Count = 1;
	DXGISwapChainDesc.SampleDesc.Quality = 0;
	DXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	DXGISwapChainDesc.BufferCount = 2;
	DXGISwapChainDesc.OutputWindow = hWnd;
	DXGISwapChainDesc.Windowed = TRUE;
	DXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	DXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	if(FAILED(m_pGIFactory->CreateSwapChain(m_pDevice, &DXGISwapChainDesc, &m_pGISwapChain))){
		errMsg = "ス?ップチェイ?作成失敗";

		Release();
		return false;
	}

	// ス?ップチェイ?からバックバッファ取得
	ID3D11Texture2D* pBackBuffer;
	if (FAILED(m_pGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer))) {
		errMsg = "バックバッファ取得失敗";

		Release();
		return false;
	}

	// バックバッファ?ソースからビ?ーを作成
	m_backBuffer = std::make_shared<KdTexture>();
	if (m_backBuffer->Create(pBackBuffer) == false)
	{
		errMsg = "バックバッファ作成失敗";
		Release();
		return false;
	}

	pBackBuffer->Release();

	/*
	// ALT+Enterでフ?スク?ー?不可にする
	{
		IDXGIDevice* pDXGIDevice;
		m_pDevice->QueryInterface<IDXGIDevice>(&pDXGIDevice);

		IDXGIAdapter* pDXGIAdapter;
		pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

		IDXGIFactory* pIDXGIFactory;
		pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pIDXGIFactory);

		pIDXGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);

		pDXGIDevice->Release();
		pDXGIAdapter->Release();
		pIDXGIFactory->Release();
	}
	*/

	//=========================================================
	// Zバッファ作成
	//=========================================================
	{
		// バッファ作成
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.Format = DXGI_FORMAT_R32_TYPELESS;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		desc.Width = (UINT)w;
		desc.Height = (UINT)h;
		desc.CPUAccessFlags = 0;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		m_zBuffer = std::make_shared<KdTexture>();
		if (m_zBuffer->Create(desc) == false)
		{
			errMsg = "Zバッファ作成失敗";
			Release();
			return false;
		}
	}

	//=========================================================
	// バックバッファ、Zバッファを描画ターゲットとしてデバイスコ?テキストへセットする
	//=========================================================
	{
		ID3D11RenderTargetView* rtvs[] = { m_backBuffer->GetRTView() };
		m_pDeviceContext->OMSetRenderTargets(1, rtvs, m_zBuffer->GetDSView());
	}

	//=========================================================
	// ビ?ーポートの設定
	//=========================================================
	{
		// ビ?ーポートの設定
		D3D11_VIEWPORT vp;
		vp.Width = (float)w;
		vp.Height = (float)h;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pDeviceContext->RSSetViewports(1, &vp);
	}

	//=========================================================
	// ブ??ドステートセットをセットしておく
	//=========================================================

	// ブ??ドステートセット
	ID3D11BlendState* bs = CreateBlendState(KdBlendMode::Alpha);
	GetDevContext()->OMSetBlendState(bs, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
	bs->Release();

	// サ?プ?ーステートセット
	ID3D11SamplerState* ss0 = CreateSamplerState(KdSamplerFilterMode::Anisotropic, 4, KdSamplerAddressingMode::Wrap, false);
	// 各シェーダへセット
	GetDevContext()->VSSetSamplers(0, 1, &ss0);
	GetDevContext()->PSSetSamplers(0, 1, &ss0);
	GetDevContext()->GSSetSamplers(0, 1, &ss0);
	GetDevContext()->CSSetSamplers(0, 1, &ss0);
	ss0->Release();

	ID3D11SamplerState* ss1 = CreateSamplerState(KdSamplerFilterMode::Anisotropic, 4, KdSamplerAddressingMode::Clamp, false);
	// 各シェーダへセット
	GetDevContext()->VSSetSamplers(1, 1, &ss1);
	GetDevContext()->PSSetSamplers(1, 1, &ss1);
	GetDevContext()->GSSetSamplers(1, 1, &ss1);
	GetDevContext()->CSSetSamplers(1, 1, &ss1);
	ss1->Release();

	// ?スタ?イザーステートセット
	ID3D11RasterizerState* rs = CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID, true, false);
	GetDevContext()->RSSetState(rs);
	rs->Release();

	// 深度ステ?シ?ステートセット
	ID3D11DepthStencilState* ds = CreateDepthStencilState(true, true);
	GetDevContext()->OMSetDepthStencilState(ds, 0);
	ds->Release();

	//=========================================================
	// 1x1の?テクスチ?作成
	//=========================================================
	{
		// 0xAABBGGRR
		auto col = Math::Color(1, 1, 1, 1).RGBA();
		D3D11_SUBRESOURCE_DATA srd;
		srd.pSysMem = &col;
		srd.SysMemPitch = 4;
		srd.SysMemSlicePitch = 0;

		m_texWhite = std::make_shared<KdTexture>();
		m_texWhite->Create(1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, 1, &srd);
	}

	// DrawVertices用頂点バッファを作成
	UINT bufferSize = 80;
	for (int i = 0; i < 10; i++)	// 
	{
		m_tempFixedVertexBuffer[i].Create(D3D11_BIND_VERTEX_BUFFER, bufferSize, D3D11_USAGE_DYNAMIC, nullptr);

		bufferSize *= 2;	// 容量を倍にしていく
	}


	return true;
}

void KdDirect3D::Release()
{
	for (auto&& n : m_tempFixedVertexBuffer)
	{
		n.Release();
	}
	m_tempVertexBuffer.Release();

	m_backBuffer = nullptr;
	m_zBuffer = nullptr;
	m_texWhite = nullptr;

	KdSafeRelease(m_pGISwapChain);
	KdSafeRelease(m_pGIAdapter);
	KdSafeRelease(m_pGIFactory);
	KdSafeRelease(m_pDeviceContext);
	KdSafeRelease(m_pDevice);

}

ID3D11DepthStencilState* KdDirect3D::CreateDepthStencilState(bool zEnable, bool zWriteEnable) const
{
	// Zバッファの動作設定
	D3D11_DEPTH_STENCIL_DESC desc = {};

	desc.DepthEnable = zEnable;							// 深度テストを使用する
	desc.DepthWriteMask = zWriteEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	desc.StencilEnable = FALSE;
	desc.StencilReadMask = 0;
	desc.StencilWriteMask = 0;

	// ステートオブジェクトを作成
	ID3D11DepthStencilState* state = nullptr;
	if (FAILED(m_pDevice->CreateDepthStencilState(&desc, &state)))return nullptr;

	return state;
}

ID3D11RasterizerState* KdDirect3D::CreateRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool depthClipEnable, bool scissorEnable) const
{
	// ?スタ?イズの動作設定
	D3D11_RASTERIZER_DESC desc = {};
	desc.FillMode = fillMode;
	desc.CullMode = cullMode;
	desc.FrontCounterClockwise = FALSE;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0;
	desc.SlopeScaledDepthBias = 0;
	desc.DepthClipEnable = depthClipEnable;
	desc.ScissorEnable = scissorEnable;
	desc.MultisampleEnable = FALSE;
	desc.AntialiasedLineEnable = FALSE;

	// ステートオブジェクト作成
	ID3D11RasterizerState* state = nullptr;
	if (FAILED(m_pDevice->CreateRasterizerState(&desc, &state)))return nullptr;

	return state;
}

ID3D11SamplerState* KdDirect3D::CreateSamplerState(KdSamplerFilterMode filterType, UINT maxAnisotropy, KdSamplerAddressingMode addressingMode, bool comparisonModel) const
{
	D3D11_SAMPLER_DESC desc = {};
	// フィ?タ
	switch (filterType) {
		// Point
	case KdSamplerFilterMode::Point:
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;
		// Linear
	case KdSamplerFilterMode::Linear:
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
		// Anisotropic
	case KdSamplerFilterMode::Anisotropic:
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		desc.MaxAnisotropy = maxAnisotropy;
		break;
	}

	// アド?ッシ?グ?ード
	switch (addressingMode) {
		// Wrap
	case KdSamplerAddressingMode::Wrap:
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
		// Clamp
	case KdSamplerAddressingMode::Clamp:
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	}

	// 比較?ードサ?プ?
	if (comparisonModel) {
		desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
		desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;	// とり?えず今回は線形フィ?タ固定で
	}
	// 通常サ?プ?
	else {
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	}

	// 
	desc.MipLODBias = 0;
	desc.BorderColor[0] = desc.BorderColor[1] = desc.BorderColor[2] = desc.BorderColor[3] = 0;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	// ステートオブジェクト作成
	ID3D11SamplerState* state = nullptr;
	if (FAILED(m_pDevice->CreateSamplerState(&desc, &state)))return nullptr;

	return state;
}

ID3D11BlendState* KdDirect3D::CreateBlendState(KdBlendMode mode) const
{
	D3D11_BLEND_DESC desc = {};
	// 有効
	desc.RenderTarget[0].BlendEnable = TRUE;
	// ?き?みマスク　R,G,B,A全て出力する場?はALL
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	desc.IndependentBlendEnable = FALSE;
	desc.AlphaToCoverageEnable = FALSE;

	// ブ??ドなし
	if (mode == KdBlendMode::NoBlend)
	{
		// 色の?成方法
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		// ア?ファの?成方法
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	}
	// 半透明ブ??ド
	else if (mode == KdBlendMode::Alpha)
	{
		// 色の?成方法
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		// ア?ファの?成方法
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	}
	// 加算ブ??ド
	else if (mode == KdBlendMode::Add)
	{
		// 色の?成方法
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		// ア?ファの?成方法
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	}
	else if (mode == KdBlendMode::Stencil)//2021/10/25 ryu
	{
		// 色の?成方法
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
		// ア?ファの?成方法
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	}
	// ステートオブジェクト作成
	ID3D11BlendState* state = nullptr;
	if (FAILED(m_pDevice->CreateBlendState(&desc, &state)))return nullptr;

	return state;
}

void KdDirect3D::SetBlendState(KdBlendMode mode)
{

	ID3D11BlendState* state;
	state = CreateBlendState(mode);

	m_pDeviceContext->OMSetBlendState(state, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
	state->Release();

}

void KdDirect3D::DrawVertices(D3D_PRIMITIVE_TOPOLOGY topology,int vertexCount, const void* pVertexStream, UINT stride)
{
	
	// プ?ミティブトポ?ジーをセット
	GetDevContext()->IASetPrimitiveTopology(topology);

	// 全頂点の?バイトサイズ
	UINT totalSize = vertexCount * stride;


	// 最適な固定長バッファを?索
	KdBuffer* buffer = nullptr;
	for (auto&& n : m_tempFixedVertexBuffer)
	{
		if (totalSize < n.GetBufferSize())
		{
			buffer = &n;
			break;
		}
	}
	// 可変長のバッファを使用
	if (buffer == nullptr)
	{
		buffer = &m_tempVertexBuffer;

		// 頂点バッファのサイズが小さいときは、?サイズのため再作成する
		if (m_tempVertexBuffer.GetBufferSize() < totalSize) {
			m_tempVertexBuffer.Create(D3D11_BIND_VERTEX_BUFFER, totalSize, D3D11_USAGE_DYNAMIC, nullptr);
		}
	}

	//============================================================
	//
	// 単?なDISCARDでの?き?み。
	//  DISCARDは、新たなバッファを内?で作成し、前回のバッファは使い終わると無効にするものです。
	//  つまり?き?む度に新規のバッファになる感じです。
	//  バッファのサイズが大きいと、その分新規のバッファを作成する?間がかかってしまいます。
	//  これを改善したい場?は、「DISCARDとNO_OVERWRITEの組み?わせ技」の方法で行うほうがよいです。
	//
	//============================================================

	// 全頂点をバッファに?き?み(DISCARD指定)
	buffer->WriteData(pVertexStream, totalSize);

	// 頂点バッファーをデバイスへセット
	{
		UINT offset = 0;
		D3D.GetDevContext()->IASetVertexBuffers(0, 1, buffer->GetAddress(), &stride, &offset);
	}

	// 描画
	GetDevContext()->Draw(vertexCount, 0);
	
}


