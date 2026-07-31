/*
 * FileName:     GameContext.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/31
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
	, m_pIGameObjectManager{}
	, m_pISceneManager{}
	, m_pIGameInput{}
{
}

// 初期化処理
void GameContext::Initialize
(
	Systems::IWindowController* pIWindowController,
	Systems::IInput*            pIInput,
	IComponentManager*          pIComponentManager,
	IGameObjectManager*         pIGameObjectManager,
	ISceneManager*              pISceneManager,
	IGameInput*                 pIGameInput
)
{
	m_pIWindowController  = pIWindowController;
	m_pIInput             = pIInput;
	m_pIComponentManager  = pIComponentManager;
	m_pIGameObjectManager = pIGameObjectManager;
	m_pISceneManager      = pISceneManager;
	m_pIGameInput         = pIGameInput;
}
