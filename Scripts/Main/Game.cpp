/*
 * FileName:     Game.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * ゲーム
 */

#include "Pch.h"
#include "Game.h"

#include "Scripts/Scenes/Scenes.h"
#include "Scripts/Commons/Renderings/Model3D.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/Colliders/BoxCollider.h"
#include "Scripts/Commons/Colliders/SphereCollider.h"
#include "Scripts/Commons/Components/RectTransform.h"

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
	, m_errorMessage{}
	, m_componentManager{}
	, m_gameObjectManager{ m_resources }
	, m_sceneManager{ m_context }
	, m_context{}
{
}

// 初期化処理
void Game::Initialize(const HWND& hWindow)
{
	// ウィンドウハンドルを保持
	m_hWindow = hWindow;

	// エラーメッセージの初期化
	m_errorMessage.Initialize(L"GenEi M Gothic v2", 5.0f, true);

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
	m_renderer.Initialize(device, context, swapChain, commonStates);
	m_renderer.CreateFontCollection(L"Resources/Fonts");

	// 画像の読み込み
	m_resources.LoadImageSources(device, L"Resources/Images");
	// モデルソースの読み込み
	m_resources.LoadModelSources(device, fx, L"Resources/Models");
	// Jsonの読み込み
	m_resources.LoadJsons(L"Resources/Jsons");

	// タイマーの初期化
	m_timer.Initialize();

	// ウィンドウ管理の初期化
	m_windowController.Initialize(hWindow);
	// 入力の初期化
	m_input.Initialize();

	// ゲームオブジェクト管理の初期化
	m_gameObjectManager.Initialize(&m_componentManager);

	// 対応付け
	RegisterComponents();

	// コンポーネント管理のインタフェース
	IComponentManager* pIComponentManager = &m_componentManager;

	// エラーメッセージのオブジェクトを生成
	m_errorMessage.CreateObjects(pIComponentManager);

	// シーンの追加
	m_sceneManager.AddScene<SampleScene>([pIComponentManager]
	{
		return std::unique_ptr<SampleScene>{ static_cast<SampleScene*>(pIComponentManager->Create<SampleScene>().release()) };
	});
	m_sceneManager.AddScene<TitleScene>([pIComponentManager]
	{
		return std::unique_ptr<TitleScene>{ static_cast<TitleScene*>(pIComponentManager->Create<TitleScene>().release()) };
	});
	// シーン管理の初期化
	m_sceneManager.Initialize(m_windowController.GetOutputSize(), pIComponentManager);

	// コンテキストの初期化
	m_context.Initialize
	(
		&m_windowController,
		&m_input,
		&m_componentManager,
		&m_gameObjectManager,
		&m_sceneManager
	);

	// 最初のシーンを設定
	m_sceneManager.SetFirstScene<TitleScene>();
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
	// F3で描画モード切り替え
	if (m_input.GetKeyDown(KeyName::F3))
	{
		m_renderer.ChangeRenderMode();
	}

	// シーン管理の更新
	m_sceneManager.Update(m_timer.GetDeltaTime());

	// エラーメッセージの更新
	m_errorMessage.Update(m_timer.GetDeltaTime());
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

	m_sceneManager.OnWindowSizeChanged(outputSize);
}

// 対応付け
void Game::RegisterComponents()
{
	// 3Dモデル
	m_componentManager.RegisterCreate<Renderings::Model3D>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Renderings::Model3D>(permit, pOwner, &m_renderer.GetIModelRenderer());
	});
	// 画像
	m_componentManager.RegisterCreate<Renderings::Image>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Renderings::Image>(permit, pOwner, &m_renderer.GetIImageRenderer());
	});
	// テキスト
	m_componentManager.RegisterCreate<Renderings::Text>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Renderings::Text>(permit, pOwner, &m_renderer.GetITextRenderer());
	});

	// 長方形の当たり判定
	m_componentManager.RegisterCreate<Colliders::BoxCollider>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Colliders::BoxCollider>(permit, pOwner, &m_renderer.GetIColliderRenderer());
	});
	// 球の当たり判定
	m_componentManager.RegisterCreate<Colliders::SphereCollider>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Colliders::SphereCollider>(permit, pOwner, &m_renderer.GetIColliderRenderer());
	});

	// 2D用トランスフォーム
	m_gameObjectManager.RegisterAdd<RectTransform>("RectTransform");
	// 画像
	m_gameObjectManager.RegisterAdd<Renderings::Image>("Image");
	// キャンバス
	m_gameObjectManager.RegisterAdd<Renderings::Canvas>("Canvas");
}
