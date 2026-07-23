/*
 * FileName:     SampleScene.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/22
 *
 * サンプルシーン
 */

#include "Pch.h"
#include "SampleScene.h"

#include "Scripts/Commons/Systems/IWindowController.h"
#include "Scripts/Commons/Systems/IInput.h"
#include "Scripts/Commons/Scenes/ISceneManager.h"
#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/GameObjects/IGameObjectManager.h"
#include "Scripts/Commons/Components/Transform.h"
#include "Scripts/Commons/Components/RectTransform.h"
#include "Scripts/Commons/Renderings/Model3D.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/Renderings/CameraScreen.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/Colliders/BoxCollider.h"
#include "Scripts/Commons/Colliders/SphereCollider.h"
#include "Scripts/GameObjects/Objects/DebugCamera/DebugCamera.h"
#include "Scripts/GameObjects/Objects/DebugCamera/DebugCameraFactory.h"
#include "Scripts/Main/GameContext.h"

// コンストラクタ
SampleScene::SampleScene(const ComponentDesc& desc)
	: Scene{ desc }
	, m_test3D{}
	, m_ground{}
	, m_pCameraScreen{}
	, m_pDebugCamera{}
	, m_pCanvas{}
{
}

// 初期化処理
void SampleScene::Initialize(const SceneTransitionData& data)
{
	// コンテキスト
	const auto& gameContext = GetContext();

	// 出力サイズ
	const Math::Vector2& outputSize = gameContext.GetPIWindowController()->GetOutputSize();

	// コンポーネント工場
	auto* pIComponentManager = gameContext.GetPIComponentManager();
	// ゲームオブジェクト管理
	auto* pIGameObjectManager = gameContext.GetPIGameObjectManager();

	pIGameObjectManager->SetPGameObjects(GetPGameObjects());
	pIGameObjectManager->Load("Scene_Sample");

	// デバッグカメラを取得
	GameObject* pCamera = pIGameObjectManager->Find("DebugCamera");
	m_pCameraScreen = pCamera->GetComponent<Renderings::CameraScreen<Camera::EulerTargetCamera>>();
	m_pCameraScreen->SetProjectionMatrix(outputSize);
	m_pDebugCamera = pCamera->GetComponent<DebugCamera>();

	// キャンバスを取得
	m_pCanvas = pIGameObjectManager->Find("Canvas")->GetComponent<Renderings::Canvas>();
	m_pCanvas->SetSize(outputSize);

	// プレイヤーを取得
	GameObject* pPlayer = pIGameObjectManager->Find("Player");
	pPlayer->GetComponent<Colliders::BoxCollider>()->ApplyTransform();
	pPlayer->GetComponent<Colliders::SphereCollider>()->ApplyTransform();
}

// 更新処理
void SampleScene::Update(float elapsedTime)
{
	// 入力管理
	auto* pIInput = GetContext().GetPIInput();

	// F5でシーン移動
	if (pIInput->GetKeyDown(KeyName::F5))
	{
		GetContext().GetPISceneManager()->SetNextScene<SampleScene>();
		return;
	}

	// カメラの更新
	m_pDebugCamera->SetInput
	(
		pIInput->GetMouseMovement(),
		pIInput->GetMouseButton(MouseButtonName::Right),
		pIInput->GetMouseButton(MouseButtonName::Middle),
		pIInput->GetMouseWheelDelta()
	);
	m_pDebugCamera->Update(elapsedTime);
	m_pCameraScreen->UpdateViewMatrix();
}

// 終了処理
void SampleScene::Finalize()
{
}

// メッセージを受け取る
void SampleScene::AcceptMessage(const std::string& message)
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
