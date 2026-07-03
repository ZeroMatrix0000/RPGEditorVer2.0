/*
 * FileName:     GameContext.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * ゲームコンテキスト
 */

#include "Pch.h"
#include "GameContext.h"

// コンストラクタ
GameContext::GameContext()
	: OnlyOne{ typeid(GameContext) }
	, m_pIWindowController{}
	, m_pComponentFactory{}
	, m_pISceneManager{}
{
}

// 初期化処理
void GameContext::Initialize
(
	Systems::IWindowController* pIWindowController,
	ComponentFactory* pComponentFactory,
	Scenes::ISceneManager<SceneTransitionData>* pISceneManager
)
{
	m_pIWindowController = pIWindowController;
	m_pComponentFactory = pComponentFactory;
	m_pISceneManager = pISceneManager;
}
