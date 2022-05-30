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

	// çXêV??
	virtual void Update();
	// ï`âÊ??
	virtual void Draw();

protected:

	ID3D11BlendState* m_BlendAlpha;

	ID3D11BlendState* m_BlendAdd;

};