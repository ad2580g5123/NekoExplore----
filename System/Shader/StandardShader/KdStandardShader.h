#pragma once

//============================================================
//
// ��{�V�F�[�_
//
//============================================================
class KdStandardShader
{
public:

	//================================================
	// �ݒ�E�擾
	//================================================

	// ?�[?�h�s��Z�b�g
	void SetWorldMatrix(const Math::Matrix& m)
	{
//		m_cb0.Work().mW = m;
		m_mTransform = m;
	}
	void SetWorldMatrixMw(const Math::Matrix& m)
	{
		m_cb0.Work().mW = m;
	}

	// UV�^�C??�O�ݒ�
	void SetUVTiling(const Math::Vector2& tiling)
	{
		m_cb0.Work().UVTiling = tiling;
	}
	// UV�I�t�Z�b�g�ݒ�
	void SetUVOffset(const Math::Vector2& offset)
	{
		m_cb0.Work().UVOffset = offset;
	}

	// ?�C�g�L��/����
	void SetLightEnable(bool enable)
	{
		m_cb0.Work().LightEnable = enable;
	}

	// �A?�t�@�e�X�g��?�l�ݒ�
	// �Ealpha	�c ���̒l�ȉ��̃A?�t�@�l�̃s�N�Z?�͕`�悳��Ȃ��Ȃ�
	void SetAlphaTestThreshold(float alpha)
	{
		m_cb0.Work().AlphaTestThreshold = alpha;
	}

	//---------------------
	// �ގ��p??�[�^�ݒ�
	//---------------------

	// ��{�F�ݒ�
	void SetBaseColor(const Math::Vector4& color)
	{
		m_cb1_Material.Work().BaseColor = color;
	}

	// ���Ȕ����F�ݒ�
	void SetEmissive(const Math::Vector3& color)
	{
		m_cb1_Material.Work().Emissive = color;
	}

	// �e���̐ݒ�
	void SetRoughness(float roughness)
	{
		m_cb1_Material.Work().Roughness = roughness;
	}

	// �����x�̐ݒ�
	void SetMetallic(float metallic)
	{
		m_cb1_Material.Work().Metallic = metallic;
	}


	// Set�n�ŃZ�b�g�����f�[�^���A���ۂɒ�?�o�b�t�@��?��?��
	void WriteToCB()
	{
		m_cb0.Write();
		m_cb1_Material.Write();
	}


	//================================================
	// �`��
	//================================================

	// ���̃V�F�[�_���f�o�C�X�փZ�b�g
	void SetToDevice();

	// ?�b�V?�`��
	// �Emesh			�c �`�悷��?�b�V?
	// �Ematerials		�c �g�p����ގ��z��
	void DrawModel(const KdModel* model,  const float _alpha=1.0f,const std::vector<Math::Matrix>* nodeTransforms = nullptr);

	//================================================
	// ?�����E���
	//================================================

	// ?����
	bool Init();
	// ���
	void Release();
	// 
	~KdStandardShader()
	{
		Release();
	}


private:

	// 3D?�f?�p�V�F�[�_
	ID3D11VertexShader*	m_VS = nullptr;				// ���_�V�F�[�_�[
	ID3D11InputLayout*	m_inputLayout = nullptr;	// ���_����?�C�A�E�g

	ID3D11PixelShader*	m_PS = nullptr;				// �s�N�Z?�V�F�[�_�[

	// �s���?�p
	Math::Matrix		m_mTransform;

	// ��?�o�b�t�@
	//  ����?�o�b�t�@�́A�p�b�L?�O�K���Ƃ������̂����炵�Ȃ���΂Ȃ�Ȃ�
	//  <�p�b�L?�O�K��> �Q�l�Fhttps://docs.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-packing-rules
	//  �E�\���̂̃T�C�Y��16�o�C�g�̔{?�ɂ���B
	//  �E�e?��(��?)�́A16�o�C�g���E���܂����悤�ȏ�?�A?�̃x�N�g?�ɔz�u�����B

	// ��?�o�b�t�@(�I�u�W�F�N�g�P�ʍX�V)
	struct cbObject
	{
		Math::Matrix		mW;		// ?�[?�h�s��@�s���16�o�C�gx4�o�C�g��64�o�C�g�Ȃ̂Ńs�b�^?�B

		// UV?��
		Math::Vector2		UVOffset = { 0,0 };
		Math::Vector2		UVTiling = { 1,1 };

		// ?�C�g�L��
		int					LightEnable = 1;
		// �A?�t�@�e�X�g��?�l
		float				AlphaTestThreshold = 0;

		float tmp[2];
	};
	KdConstantBuffer<cbObject>	m_cb0;

	// ��?�o�b�t�@(�}�e?�A?�P�ʍX�V)
	struct cb {
		Math::Vector4	BaseColor;
		Math::Vector3	Emissive;
		float			Metallic;
		float			Roughness;

		float			tmp[3];
	};
	KdConstantBuffer<cb>	m_cb1_Material;

};


