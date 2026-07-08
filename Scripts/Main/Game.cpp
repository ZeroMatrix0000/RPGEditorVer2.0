/*
 * FileName:     Game.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * ゲーム
 */

#include "Pch.h"
#include "Game.h"

#include "Scripts/Scenes/Scenes.h"
#include "Scripts/Commons/Renderings/Model3D.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/Renderings/CameraScreen.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/GameObjects/Transform.h"
#include "Scripts/Commons/GameObjects/RectTransform.h"
#include "Scripts/Commons/Colliders/BoxCollider.h"
#include "Scripts/Commons/Colliders/SphereCollider.h"
#include "../Objects/DebugCamera/DebugCamera.h"

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
	m_errorMessage.Initialize(L"Makinas 4 Flat", 5.0f);

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
	m_renderer.CreateFontCollection(std::vector<std::wstring>
	{
		L"Resources/Fonts/Makinas-4-Flat.otf",
		L"Resources/Fonts/GenEiMGothic2-Medium.ttf"
	});

	// リソースの追加
	AddResources(device, fx);
	// タイマーの初期化
	m_timer.Initialize();

	// ウィンドウ管理の初期化
	m_windowController.Initialize(hWindow);
	// 入力の初期化
	m_input.Initialize();

	// コンポーネント工場の初期化
	AddComponents();

	// コンポーネント管理のインタフェース
	const IComponentManager& iComponentManager = m_componentManager;

	// エラーメッセージのオブジェクトを生成
	m_errorMessage.CreateObjects(iComponentManager);

	// シーンの追加
	m_sceneManager.AddScene<SampleScene>([&]
	{
		return std::unique_ptr<SampleScene>{ static_cast<SampleScene*>(iComponentManager.Create<SampleScene>().release()) };
	});
	// シーン管理の初期化
	m_sceneManager.Initialize(m_windowController.GetOutputSize(), iComponentManager);

	// コンテキストの初期化
	m_context.Initialize
	(
		&m_windowController,
		&m_input,
		&m_componentManager,
		&m_sceneManager
	);

	// 最初のシーンを設定
	m_sceneManager.SetFirstScene<SampleScene>();
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

// コンポーネントの追加
void Game::AddComponents()
{
	// トランスフォーム
	m_componentManager.AddComponent<Transform>();
	// 2D用トランスフォーム
	m_componentManager.AddComponent<RectTransform>();
	// 3Dモデル
	m_componentManager.AddComponent<Renderings::Model3D>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Renderings::Model3D>(permit, pOwner, &m_renderer.GetIModelRenderer());
	});
	// 画像
	m_componentManager.AddComponent<Renderings::Image>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Renderings::Image>(permit, pOwner, &m_renderer.GetIImageRenderer());
	});
	// テキスト
	m_componentManager.AddComponent<Renderings::Text>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Renderings::Text>(permit, pOwner, &m_renderer.GetITextRenderer());
	});
	// カメラ画面
	m_componentManager.AddComponent<Renderings::CameraScreen<Camera::QuaternionCamera>>();
	// カメラ画面
	m_componentManager.AddComponent<Renderings::CameraScreen<Camera::QuaternionTargetCamera>>();
	// カメラ画面
	m_componentManager.AddComponent<Renderings::CameraScreen<Camera::EulerCamera>>();
	// カメラ画面
	m_componentManager.AddComponent<Renderings::CameraScreen<Camera::EulerTargetCamera>>();
	// キャンバス
	m_componentManager.AddComponent<Renderings::Canvas>();

	// 長方形の当たり判定
	m_componentManager.AddComponent<Colliders::BoxCollider>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Colliders::BoxCollider>(permit, pOwner, &m_renderer.GetIColliderRenderer());
	});
	// 球の当たり判定
	m_componentManager.AddComponent<Colliders::SphereCollider>([&](const ComponentCreatePermit& permit, GameObject* pOwner)
	{
		return std::make_unique<Colliders::SphereCollider>(permit, pOwner, &m_renderer.GetIColliderRenderer());
	});

	// サンプルシーン
	m_componentManager.AddComponent<SampleScene>();

	// デバッグ用カメラ
	m_componentManager.AddComponent<DebugCamera>();
}
