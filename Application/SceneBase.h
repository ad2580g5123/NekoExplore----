#pragma once
class SceneBase
{
public:

	SceneBase();

	virtual ~SceneBase();

	//uppcast
	// 
	//virtual void SetCamera();

	virtual void Frame();

	// �X�V??
	virtual void Update();
	// �`��??
	virtual void Draw();

protected:

	ID3D11BlendState* m_BlendAlpha;

	ID3D11BlendState* m_BlendAdd;

};