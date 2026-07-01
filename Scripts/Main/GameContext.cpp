#include "Pch.h"
#include "GameContext.h"

// コンストラクタ
GameContext::GameContext()
	: OnlyOne{ typeid(GameContext) }
	, m_pComponentFactory{}
	, m_pISceneManager{}
{
}

// 初期化処理
void GameContext::Initialize
(
	ComponentFactory* pComponentFactory,
	Scenes::ISceneManager<SceneTransitionData>* pISceneManager
)
{
	m_pComponentFactory = pComponentFactory;
	m_pISceneManager = pISceneManager;
}
