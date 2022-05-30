#include"define.h"
#include "main.h"
#include"Headers.h"

//===================================================================
// ?イ?
//===================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	// ????ークを知らせる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// COM?期化
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	// mbstowcs_s関?で日本語対?にするために呼ぶ
	setlocale(LC_ALL, "japanese");

	//===================================================================
	// 実行
	//===================================================================
	APP.Execute();

	// COM解放
	CoUninitialize();

	return 0;
}


// アプ?ケーシ???期設定
bool Application::Init(int w, int h)
{

	//===================================================================
	// ウィ?ドウ作成
	//===================================================================
	if (m_window.Create(w, h, "Neko Explore", "Window") == false) {
		MessageBoxA(nullptr, "ウィ?ドウ作成に失敗", "エ?ー", MB_OK);
		return false;
	}

	//===================================================================
	// フ?スク?ー?確認
	//===================================================================
	bool bFullScreen = false;
	//if (MessageBoxA(m_window.GetWndHandle(), "フ?スク?ー?にしますか？", "確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
	//	bFullScreen = true;
	//}


	//===================================================================
	// Direct3D?期化
	//===================================================================

	// デバイスのデバッグ?ードを有効にする
	bool deviceDebugMode = false;
	#ifdef _DEBUG
	deviceDebugMode = true;
	#endif

	// Direct3D?期化
	std::string errorMsg;
	if (D3D.Init(m_window.GetWndHandle(), w, h, deviceDebugMode, errorMsg) == false) {
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "Direct3D?期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}

	// フ?スク?ー?設定
	if (bFullScreen) {
		D3D.GetSwapChain()->SetFullscreenState(TRUE, 0);
	}

	// シェーダー?期化
	SHADER.Init();

	//===================================================================
	// サウ?ド?期化
	//===================================================================
	if (AUDIO.Init() == false)
	{
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "サウ?ド?期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}




	return true;
}

// アプ?ケーシ??終了
void Application::Release()
{

	// シェーダ解放
	SHADER.Release();

	// Direct3D解放
	D3D.Release();

	// XAudio2解放
	AUDIO.Release();

	// ウィ?ドウ削?
	m_window.Release();

}

// アプ?ケーシ??実行
void Application::Execute()
{
	//===================================================================
	// ?期設定(ウィ?ドウ作成、Direct3D?期化など)
	//===================================================================
	if (APP.Init(ScrW, ScrH) == false) {
		return;
	}

	//===================================================================
	// ゲー??ープ
	//===================================================================

	// ?間
	DWORD baseTime = timeGetTime();
	int count = 0;

	// ゲー?イ?スタ?ス
	/*GameScene game;
	game.Init();*/
	SCENEMANAGER.ChangeScene(new TitleScene());
	// ?ープ
	while (1)
	{

		// ??開始?間Get
		DWORD st = timeGetTime();

		// ゲー?終了指定が?るときは?ープ終了
		if (m_endFlag)
		{ 
			break;
		}

		//=========================================
		//
		// ウィ?ドウ関係の??
		//
		//=========================================

		// ウィ?ドウの?ッセージを??する
		m_window.ProcessMessage();

		// ウィ?ドウが破棄されてるなら?ープ終了
		if (m_window.IsCreated() == false)
		{
			break;
		}

		//=========================================
		//
		// オーディオ??
		//
		//=========================================
		AUDIO.Update();

		//=========================================
		//
		// ゲー???
		//
		//=========================================
		/*game.Frame();*/
		SCENEMANAGER.DoScene();
		D3D.GetSwapChain()->Present(0, 0);

		//=========================================
		//
		// フ?ー??ート制御
		//
		//=========================================
		// ??終了?間Get
		DWORD et = timeGetTime();
		// Fps制御
		DWORD ms = 1000 / m_maxFps;
		if (et - st < ms)
		{
			Sleep(ms - (et - st));	// 速すぎたら待つ
		}

		// FPS計測
		count++;
		if (st - baseTime >= 500)
		{
			m_fps = (count * 1000) / (st - baseTime);
			baseTime = st;
			count = 0;
		}

	}

	//game.Release();

	//===================================================================
	// アプ?ケーシ??解放
	//===================================================================
	Release();
}