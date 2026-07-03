/*
 * FileName:     SampleScene.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * サンプルシーン
 */

#include "Pch.h"
#include "SampleScene.h"

#include "Scripts/Commons/GameObjects/Transform.h"
#include "Scripts/Commons/Renderings/Model3D.h"
#include "Scripts/Commons/Renderings/CameraScreen.h"

// コンストラクタ
SampleScene::SampleScene(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Scene{ permit, pOwner }
	, m_test{}
	, m_camera{}
{
}

// 初期化処理
void SampleScene::Initialize(const SceneTransitionData& data)
{
	// コンポーネント工場
	const auto& componentFactory = GetContext().GetComponentFactory();

	// コンポーネントをアタッチ
	auto* pTransform = m_test.AddComponent<Transform>(componentFactory);
	pTransform->SetPosition(Math::Vector3::Left * 5.0f);
	auto* pModel = m_test.AddComponent<Renderings::Model3D>(componentFactory);
	pModel->SetModelSourceName("Player");
	auto* cameraScreen = m_camera.AddComponent<Renderings::CameraScreen<Camera::EulerTargetCamera>>(componentFactory);
	cameraScreen->GetRefCamera() = Camera::EulerTargetCamera{ Math::Vector3::Zero, Math::Euler{ -30.0f, 0.0f, 0.0f }, 15.0f };
	cameraScreen->SetProjectionMatrix(45.0f, GetContext().GetIWindowController().GetOutputSize());

	// モデルにカメラ画面を設定
	pModel->SetICameraScreen(*cameraScreen);
}

// 更新処理
void SampleScene::Update(float elapsedTime)
{
	m_test.Update(elapsedTime);

	// カメラの更新
	m_camera.Update(elapsedTime);
}

// 終了処理
void SampleScene::Finalize()
{
}

// メッセージを受け取る
void SampleScene::AcceptMessage(const std::string& message)
{
	// 出力サイズ
	const Math::Vector2& outputSize = GetContext().GetIWindowController().GetOutputSize();

	if (message == "WindowSizeChanged")
	{
		// プロジェクション行列を設定
		m_camera.GetComponent<Renderings::CameraScreen<Camera::EulerTargetCamera>>()->SetProjectionMatrix(45.0f, outputSize);
	}
}
