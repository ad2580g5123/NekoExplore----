#include "Headers.h"

void SceneManager::DoScene()
{
	if (m_NowScene != m_NextScene)
	{

		if (m_NowScene != nullptr)
		{

			delete m_NowScene;

		}

		m_NowScene = m_NextScene;

	}

	if (m_NowScene != nullptr)
	{

		m_NowScene->Frame();

	}
}
void SceneManager::ChangeScene(SceneBase* _nextScene)
{

	m_NextScene = _nextScene;

}
SceneManager::SceneManager()
{
}
SceneManager::~SceneManager()
{

	if (m_NowScene != nullptr)
	{

		delete m_NowScene;

	}

}
