/*
 * FileName:     Game.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
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
	, m_renderer{ m_resources }
	, m_resources{}
	, m_timer{}
	, m_windowController{}
	, m_input{}
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

	// 描画の初期化
	m_renderer.Initialize(context, swapChain, commonStates);

	// リソースの追加
	AddResources(device, fx);
	// タイマーの初期化
	m_timer.Initialize();

	// ウィンドウ管理の初期化
	m_windowController.Initialize(hWindow);
	// 入力の初期化
	m_input.Initialize();

	// コンポーネント工場の初期化
	m_componentFactory.Initialize
	(
		&m_renderer.GetIModelRenderer(),
		&m_renderer.GetIImageRenderer(),
		&m_renderer.GetITextRenderer()
	);

	// シーンの追加
	m_sceneManager.AddScene("Sample", [&] { return m_componentFactory.Create<SampleScene>(); });

	// コンテキストの初期化
	m_context.Initialize
	(
		&m_windowController,
		&m_input,
		&m_componentFactory,
		&m_sceneManager
	);

	// 最初のシーンを設定
	m_sceneManager.SetFirstScene("Sample");
}

// 更新処理
void Game::Update()
{
	// タイマーの更新
	m_timer.Update();

	// 入力の更新
	m_input.Update();

	// F4でフルスクリーン表示切り替え
	if (m_input.GetKeyDown(KeyName::F4))
	{
		m_windowController.ChangeFullScreen();
	}

	// シーン管理の更新
	m_sceneManager.Update(m_timer.GetDeltaTime());
}

// 描画処理
void Game::Render()
{
	// ウィンドウを受け取っていないなら何もしない
	if (!m_hWindow)
	{
		return;
	}

	// 画面の初期化
	m_deviceResources.Clear();

	// 描画
	m_renderer.Render();

	// 画面の表示
	m_deviceResources.Present();
}

// 終了処理
void Game::Finalize()
{
	// シーン管理の終了
	m_sceneManager.Finalize();
}

// ウィンドウサイズ変更時の処理
void Game::OnWindowSizeChanged(const Math::Vector2Int& outputSize)
{
	// ウィンドウを受け取っていないなら何もしない
	if (!m_hWindow)
	{
		return;
	}

	// テキスト描画をリセット
	m_renderer.ResetTextRenderer();

	m_deviceResources.OnWindowSizeChanged(outputSize);
	m_windowController.SetOutputSize(outputSize);

	// テキスト描画を初期化
	m_renderer.InitializeTextRenderer(m_deviceResources.GetSwapChain());

	m_sceneManager.OnWindowSizeChanged();
}

// リソースの追加
void Game::AddResources(ID3D11Device5* device, DirectX::EffectFactory* fx)
{
	// 画像の追加
	m_resources.AddImage("Box"           , device, L"Resources/Images/Box.dds"        );
	m_resources.AddImage("InteractCursor", device, L"Resources/Images/FocusCursor.dds");
	m_resources.AddImage("DialogBoxUI"   , device, L"Resources/Images/DialogBox.dds"  );
	m_resources.AddImage("MenuDown"      , device, L"Resources/Images/MenuDown.dds"   );
	m_resources.AddImage("MenuUp"        , device, L"Resources/Images/MenuUp.dds"     );
	m_resources.AddImage("MenuRight"     , device, L"Resources/Images/MenuRight.dds"  );
	// モデルソースの追加
	m_resources.AddModelSource("Player", device, fx, L"Resources/Models/Player.cmo");
	m_resources.AddModelSource("NPC"   , device, fx, L"Resources/Models/NPC.cmo"   );
	m_resources.AddModelSource("Ground", device, fx, L"Resources/Models/Ground.cmo");
}
