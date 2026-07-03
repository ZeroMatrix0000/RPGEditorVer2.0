/*
 * FileName:     Game.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * ゲーム
 */

#include "Pch.h"
#include "Game.h"

#include "Scripts/Scenes/Scenes.h"

// コンストラクタ
Game::Game()
	: OnlyOne{ typeid(Game) }
	, m_hWindow{}
	, m_deviceResources{}
	, m_renderingResources{}
	, m_modelRenderer{ m_resources }
	, m_resources{}
	, m_windowController{}
	, m_componentFactory{}
	, m_sceneManager{ m_context }
	, m_context{}
{
}

// 初期化処理
void Game::Initialize(const HWND& hWindow)
{
	// ウィンドウハンドルを保持
	m_hWindow = hWindow;

	// デバイスリソースの初期化
	m_deviceResources.Initialize(hWindow);

	// デバイス
	auto* device = m_deviceResources.GetD3DDevice();
	// コンテキスト
	auto* context = m_deviceResources.GetD3DContext();
	// スワップチェイン
	auto* swapChain = m_deviceResources.GetSwapChain();

	// 描画リソースの初期化
	m_renderingResources.Initialize(device);
	m_renderingResources.SetEffectFactoryDirectory(L"Resources/Models");

	// コモンステート
	const auto& commonStates = m_renderingResources.GetCommonStates();
	// エフェクトファクトリー
	auto* fx = m_renderingResources.GetEffectFactory();

	// モデル描画の初期化
	m_modelRenderer.Initialize(context, commonStates);

	// リソースの追加
	AddResources(device, fx);
	// ウィンドウ管理の初期化
	m_windowController.Initialize(hWindow);

	// コンポーネント工場にモデル描画インタフェースを設定
	m_componentFactory.SetPIModelRenderer(&m_modelRenderer);

	// シーンの追加
	m_sceneManager.AddScene("Sample", [&] { return m_componentFactory.Create<SampleScene>(); });

	// コンテキストの初期化
	m_context.Initialize
	(
		&m_windowController,
		&m_componentFactory,
		&m_sceneManager
	);

	// 最初のシーンを設定
	m_sceneManager.SetFirstScene("Sample");
}

// 終了処理
void Game::Finalize()
{
	// シーン管理の終了
	m_sceneManager.Finalize();
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
	m_windowController.SetOutputSize(outputSize);
	m_sceneManager.OnWindowSizeChanged();
}

// 更新処理
void Game::Update()
{
	// シーン管理の更新
	m_sceneManager.Update(0.0f);
}

// 描画処理
void Game::Render()
{
	// 画面の初期化
	m_deviceResources.Clear();

	// モデルの描画
	m_modelRenderer.Render();

	// 画面の表示
	m_deviceResources.Present();
}

// リソースの追加
void Game::AddResources(ID3D11Device5* device, DirectX::EffectFactory* fx)
{
	// モデルソースの追加
	m_resources.AddModelSource("Player", device, fx, L"Resources/Models/Player.cmo");
	m_resources.AddModelSource("NPC"   , device, fx, L"Resources/Models/NPC.cmo");
	m_resources.AddModelSource("Ground", device, fx, L"Resources/Models/Ground.cmo");
}
