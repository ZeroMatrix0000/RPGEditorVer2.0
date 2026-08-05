/*
 * FileName:     GamePlayScene.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/05
 *
 * ゲームプレイシーン
 */

#include "Pch.h"
#include "GamePlayScene.h"

#include "Scripts/Commons/Systems/IWindowController.h"
#include "Scripts/Commons/Systems/IInput.h"
#include "Scripts/Commons/Scenes/ISceneManager.h"
#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/GameObjects/IGameObjectManager.h"
#include "Scripts/Commons/Renderings/ICameraScreen.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/Colliders/BoxCollider.h"
#include "Scripts/Commons/Colliders/SphereCollider.h"
#include "Scripts/Commons/Colliders/MeshCollider.h"
#include "Scripts/GameObjects/Objects/Player/Player.h"
#include "Scripts/GameObjects/Objects/Player/PlayerCamera.h"
#include "Scripts/Main/GameContext.h"
#include "Scripts/Main/IGameInput.h"

 // コンストラクタ
GamePlayScene::GamePlayScene(const ComponentDesc& desc)
	: Scene{ desc }
	, m_pPlayer{}
	, m_pPlayerCamera{}
	, m_pGround{}
	, m_pCameraScreen{}
	, m_pCanvas{}
{
}

// 初期化処理
void GamePlayScene::Initialize(const SceneTransitionData& data)
{
	// コンテキスト
	const auto& gameContext = GetContext();

	// マウスをループ・非表示
	gameContext.GetPIInput()->SetMousePositionLoop(true);
	gameContext.GetPIInput()->DisplayCursor(false);

	// 出力サイズ
	const Math::Vector2& outputSize = gameContext.GetPIWindowController()->GetOutputSize();

	// ゲームオブジェクト管理
	auto* pIGameObjectManager = gameContext.GetPIGameObjectManager();

	pIGameObjectManager->SetPGameObjects(GetPGameObjects());
	pIGameObjectManager->Load("Scene_GamePlay");

	// プレイヤーを取得
	m_pPlayer = pIGameObjectManager->Find("Player")->GetComponent<Player>();

	// プレイヤーカメラを取得
	GameObject* pCamera = pIGameObjectManager->Find("PlayerCamera");
	m_pCameraScreen = pCamera->GetComponent<Renderings::ICameraScreen>();
	m_pCameraScreen->UpdateViewMatrix();
	m_pCameraScreen->SetProjectionMatrix(outputSize);
	m_pPlayerCamera = pCamera->GetComponent<PlayerCamera>();

	// キャンバスを取得
	m_pCanvas = pIGameObjectManager->Find("Canvas")->GetComponent<Renderings::Canvas>();
	m_pCanvas->SetSize(outputSize);

	// 地面を取得
	m_pGround = pIGameObjectManager->Find("Ground")->GetComponent<Colliders::MeshCollider>();
	m_pGround->ApplyTransform();
}

// 更新処理
void GamePlayScene::Update(float elapsedTime)
{
	// シーン切り替え中なら何もしない
	if (GetContext().GetPISceneManager()->IsChanging())
	{
		return;
	}

	// 入力管理
	auto* pIInput = GetContext().GetPIInput();

	// F5でシーン移動
	if (pIInput->GetKeyDown(KeyName::F5))
	{
		GetContext().GetPISceneManager()->SetNextScene<GamePlayScene>();
		return;
	}

	// ゲーム入力
	auto* pIGameInput = GetContext().GetPIGameInput();

	// プレイヤーの更新
	m_pPlayer->Update(elapsedTime, pIGameInput->GetPlayerMove());
	m_pPlayer->MeshCorrect(m_pGround->GetWorldMesh());

	// カメラの更新
	m_pPlayerCamera->SetTarget(m_pPlayer->GetCameraTarget());
	m_pPlayerCamera->Rotate(pIGameInput->GetPlayerCameraRotate());
	m_pPlayerCamera->MeshCorrect(m_pGround->GetWorldMesh(), m_pPlayer->GetPosition());
	m_pPlayerCamera->Update(elapsedTime);
	m_pCameraScreen->UpdateViewMatrix();
}

// 終了処理
void GamePlayScene::Finalize()
{
	// マウスをループ解除・表示
	GetContext().GetPIInput()->SetMousePositionLoop(true);
	GetContext().GetPIInput()->DisplayCursor(false);
}

// メッセージを受け取る
void GamePlayScene::AcceptMessage(const std::string& message)
{
	if (message == "WindowSizeChanged")
	{
		// 出力サイズ
		const Math::Vector2& outputSize = GetContext().GetPIWindowController()->GetOutputSize();
		// プロジェクション行列を設定
		m_pCameraScreen->SetProjectionMatrix(outputSize);
		// キャンバスのサイズを設定
		m_pCanvas->SetSize(outputSize);
	}
}
