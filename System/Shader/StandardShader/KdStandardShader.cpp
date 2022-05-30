#include "System/KdSystem.h"

#include "KdStandardShader.h"


bool KdStandardShader::Init()
{
	//-------------------------------------
	// 頂点シェーダ
	//-------------------------------------
	{
		// コ?パイ?済みのシェーダーヘッダーファイ?をイ?ク?ード
		#include "KdStandardShader_VS.inc"

		// 頂点シェーダー作成
		if (FAILED(D3D.GetDev()->CreateVertexShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_VS))) {
			assert(0 && "頂点シェーダー作成失敗");
			Release();
			return false;
		}

		// １頂点の詳細な情報
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		// 頂点入力?イアウト作成
		if (FAILED(D3D.GetDev()->CreateInputLayout(
			&layout[0],			// 入力エ???ト先頭アド?ス
			layout.size(),		// 入力エ???ト?
			&compiledBuffer[0],				// 頂点バッファのバイナ?データ
			sizeof(compiledBuffer),			// 上記のバッファサイズ
			&m_inputLayout))					// 
		) {
			assert(0 && "CreateInputLayout失敗");
			Release();
			return false;
		}

	}

	//-------------------------------------
	// ピクセ?シェーダ
	//-------------------------------------
	{
		// コ?パイ?済みのシェーダーヘッダーファイ?をイ?ク?ード
		#include "KdStandardShader_PS.inc"

		if (FAILED(D3D.GetDev()->CreatePixelShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_PS))) {
			assert(0 && "ピクセ?シェーダー作成失敗");
			Release();
			return false;
		}
	}

	//-------------------------------------
	// 定?バッファ作成
	//-------------------------------------
	m_cb0.Create();
	m_cb1_Material.Create();

	return true;
}

void KdStandardShader::Release()
{
	KdSafeRelease(m_VS);
	KdSafeRelease(m_PS);
	KdSafeRelease(m_inputLayout);
	m_cb0.Release();
	m_cb1_Material.Release();

}

void KdStandardShader::SetToDevice()
{
	// 頂点シェーダをセット
	D3D.GetDevContext()->VSSetShader(m_VS, 0, 0);
	// 頂点?イアウトをセット
	D3D.GetDevContext()->IASetInputLayout(m_inputLayout);

	// ピクセ?シェーダをセット
	D3D.GetDevContext()->PSSetShader(m_PS, 0, 0);

	// 定?バッファをセット
	D3D.GetDevContext()->VSSetConstantBuffers(0, 1, m_cb0.GetAddress());
	D3D.GetDevContext()->PSSetConstantBuffers(0, 1, m_cb0.GetAddress());

	D3D.GetDevContext()->VSSetConstantBuffers(1, 1, m_cb1_Material.GetAddress());
	D3D.GetDevContext()->PSSetConstantBuffers(1, 1, m_cb1_Material.GetAddress());

}

/*
void KdStandardShader::DrawModel(const KdModel* model)
{
	if (model == nullptr)return;

	auto mesh = model->GetMesh();
	if (mesh == nullptr)return;

	// 定?バッファ?き?み
	m_cb0.Write();

	// ?ッシ?情報をセット
	mesh->SetToDevice();

	// 全サブセット
	for (UINT subi = 0; subi < mesh->GetSubsets().size(); subi++)
	{
		// 面が１?も無い場?はスキップ
		if (mesh->GetSubsets()[subi].FaceCount == 0)continue;

		// マテ?ア?セット
		const KdMaterial& material = model->GetMaterials()[ mesh->GetSubsets()[subi].MaterialNo ];

		//-----------------------
		// マテ?ア?情報を定?バッファへ?き?む
		//-----------------------
		m_cb1_Material.Work().BaseColor = material.BaseColor;
		m_cb1_Material.Work().Emissive = material.Emissive;
		m_cb1_Material.Work().Metallic = material.Metallic;
		m_cb1_Material.Work().Roughness = material.Roughness;
		m_cb1_Material.Write();

		//-----------------------
		// テクスチ?セット
		//-----------------------

		ID3D11ShaderResourceView* srvs[3] = {};

		// BaseColor
		srvs[0] = material.BaseColorTex->GetSRView();
		// Emissive
		srvs[1] = material.EmissiveTex->GetSRView();
		// Metallic Roughness
		srvs[2] = material.MetallicRoughnessTex->GetSRView();

		// セット
		D3D.GetDevContext()->PSSetShaderResources(0, _countof(srvs), srvs);

		//-----------------------
		// サブセット描画
		//-----------------------
		mesh->DrawSubset(subi);
	}

}
*/

void KdStandardShader::DrawModel(const KdModel* model, const float _alpha, const std::vector<Math::Matrix>* nodeTransforms)
{
	if (model == nullptr)return;

	//if (mesh == nullptr)return;

	// 全ノード内の?ッシ?を描画
	for (UINT nodei = 0; nodei < model->GetAllNodes().size(); nodei++)
	{
		// ノード
		const KdModel::Node& node = model->GetAllNodes()[nodei];
		// ?ッシ?が存在しない場?はスキップ
		if (node.Mesh == nullptr)continue;

		// ?ッシ?情報をセット
		node.Mesh->SetToDevice();

		// 行列
		if (nodeTransforms && nodei < nodeTransforms->size()) {
			m_cb0.Work().mW = (*nodeTransforms)[nodei] * m_mTransform;
		}
		else {
			m_cb0.Work().mW = node.LocalTransform * m_mTransform;
		}

		// 定?バッファ?き?み
		m_cb0.Write();

		// 全サブセット
		//std::shared_ptr<const KdMaterial> material;

		for (UINT subi = 0; subi < node.Mesh->GetSubsets().size(); subi++)
		{
			// 面が１?も無い場?はスキップ
			if (node.Mesh->GetSubsets()[subi].FaceCount == 0)continue;

			// マテ?ア?セット
			//const KdMaterial& material = materials[mesh->GetSubsets()[subi].MaterialNo];
			// マテ?ア?セット
			int matNo = -1;
			if (matNo != node.Mesh->GetSubsets()[subi].MaterialNo)
			{
				//material = node.Mesh->GetSubsets()[subi].MaterialData;
				KdMaterial material = model->GetMaterials()[node.Mesh->GetSubsets()[subi].MaterialNo];
				
				//-----------------------
				// マテ?ア?情報を定?バッファへ?き?む
				//-----------------------
				material.BaseColor.w *= _alpha;
				m_cb1_Material.Work().BaseColor = material.BaseColor;
				m_cb1_Material.Work().Emissive = material.Emissive;
				m_cb1_Material.Work().Metallic = material.Metallic;
				m_cb1_Material.Work().Roughness = material.Roughness;
				m_cb1_Material.Write();

				//-----------------------
				// テクスチ?セット
				//-----------------------

				ID3D11ShaderResourceView* srvs[3] = {};

				// BaseColor
				srvs[0] = material.BaseColorTex->GetSRView();
				// Emissive
				srvs[1] = material.EmissiveTex->GetSRView();
				// Metallic Roughness
				srvs[2] = material.MetallicRoughnessTex->GetSRView();

				// セット
				D3D.GetDevContext()->PSSetShaderResources(0, _countof(srvs), srvs);
			}

			//-----------------------
			// サブセット描画
			//-----------------------
			node.Mesh->DrawSubset(subi);
		}

	}
}


