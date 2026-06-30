/*
 * FileName:     Game.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * ゲーム
 */

#include "Pch.h"
#include "Game.h"

// コンストラクタ
Game::Game()
	: OnlyOne{ typeid(Game) }
	, m_hWindow{}
	, m_deviceResources{}
	, m_componentFactory{}
{
}

// 初期化処理
void Game::Initialize(const HWND& hWindow)
{
	// ウィンドウハンドルを保持
	m_hWindow = hWindow;

	// デバイスリソースの初期化
	m_deviceResources.Initialize(hWindow);
}

// 終了処理
void Game::Finalize()
{
}

// 毎フレーム呼ぶ処理
void Game::Tick()
{
	// 更新処理
	Update();
	// 描画処理
	Render();
}

// ウィンドウサイズ変更時の処理
void Game::OnWindowSizeChanged(const Math::Vector2Int& outputSize)
{
	// ウィンドウを受け取っていないなら何もしない
	if (!m_hWindow)
	{
		return;
	}

	m_deviceResources.OnWindowSizeChanged(outputSize);
}

// 更新処理
void Game::Update()
{
}

// 描画処理
void Game::Render()
{
	// 画面の初期化
	m_deviceResources.Clear();

	// 画面の表示
	m_deviceResources.Present();
}
