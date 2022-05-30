#pragma once
class SceneManager
{
public:

	void DoScene();

	void ChangeScene(SceneBase* _nextScene);

	static SceneManager& GetInstance()
	{

		static SceneManager instance;

		return instance;

	}

private:

	SceneManager();

	~SceneManager();

	SceneBase* m_NowScene = nullptr;

	SceneBase* m_NextScene = nullptr;

};
#define SCENEMANAGER SceneManager::GetInstance()