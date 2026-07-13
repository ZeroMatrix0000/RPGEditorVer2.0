/*
 * FileName:     GameContext.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * ゲームコンテキスト
 */

#include "Pch.h"
#include "GameContext.h"

// コンストラクタ
GameContext::GameContext()
	: OnlyOne{ typeid(GameContext) }
	, m_pIWindowController{}
	, m_pIInput{}
	, m_pIComponentManager{}
	, m_pISceneManager{}
{
}

// 初期化処理
void GameContext::Initialize
(
	Systems::IWindowController* pIWindowController,
	Systems::IInput*            pIInput,
	IComponentManager*          pIComponentManager,
	ISceneManager*              pISceneManager
)
{
	m_pIWindowController = pIWindowController;
	m_pIInput            = pIInput;
	m_pIComponentManager = pIComponentManager;
	m_pISceneManager     = pISceneManager;
}
