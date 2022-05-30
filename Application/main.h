#pragma once


//============================================================
// アプ?ケーシ??ク?ス
//	APP.～ でどこからでもアクセス可能
//============================================================
class Application
{
// ??バ
public:

	// アプ?ケーシ??実行
	void Execute();

	// アプ?ケーシ??終了
	void End() { m_endFlag = true; }


	//=====================================================
	// グ?ーバ?データ
	//=====================================================

	// ゲー?ウィ?ドウク?ス
	KdWindow		m_window;

	// FPS制御
	int				m_fps = 0;					// 現在のFPS値
	int				m_maxFps = 60;				// 最大FPS


private:

	// アプ?ケーシ???期化
	bool Init(int w, int h);

	// アプ?ケーシ??解放
	void Release();

	// ゲー?終了フ?グ trueで終了する
	bool		m_endFlag = false;


//=====================================================
// シ?グ?ト?パター?
//=====================================================
private:
	// 
	Application() {}

public:
	static Application &GetInstance(){
		static Application Instance;
		return Instance;
	}
};

// 簡単にアクセスできるようにするためのマク?
#define APP Application::GetInstance()
