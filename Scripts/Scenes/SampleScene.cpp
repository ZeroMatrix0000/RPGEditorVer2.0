/*
 * FileName:     SampleScene.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * サンプルシーン
 */

#include "Pch.h"
#include "SampleScene.h"

#include "Scripts/Commons/GameObjects/Transform.h"
#include "Scripts/Commons/GameObjects/RectTransform.h"
#include "Scripts/Commons/Renderings/Model3D.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/Renderings/CameraScreen.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/Colliders/BoxCollider.h"
#include "Scripts/Commons/Colliders/SphereCollider.h"
#include "../Objects/DebugCamera/DebugCamera.h"
#include "../Objects/DebugCamera/DebugCameraFactory.h"
#include "../Main/GameContext.h"

// コンストラクタ
SampleScene::SampleScene(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Scene{ permit, pOwner }
	, m_test3D{}
	, m_test2D{}
	, m_test2D2{}
	, m_ground{}
	, m_camera{}
	, m_pCameraScreen{}
	, m_pDebugCamera{}
	, m_canvas{}
{
}

// 初期化処理
void SampleScene::Initialize(const SceneTransitionData& data)
{
	// 出力サイズ
	const Math::Vector2& outputSize = GetContext().GetIWindowController().GetOutputSize();

	// コンポーネント工場
	const auto& iComponentManager = GetContext().GetIComponentManager();

	// デバッグカメラを作成
	DebugCameraFactory::Create(iComponentManager, outputSize, &m_camera, &m_pCameraScreen, &m_pDebugCamera);

	auto* pCanvas = m_canvas.AddComponent<Renderings::Canvas>(iComponentManager);
	pCanvas->Initialize(Renderings::Canvas::FixedSize::Vertical, outputSize);

	{
		auto* pTransform = m_test3D.AddComponent<Transform>(iComponentManager);
		pTransform->SetPosition(Math::Vector3::Left * 5.0f);
		pTransform->SetRotation(Math::Euler{ 0.0f, 45.0f, 0.0f }.CreateQuaternion());
		pTransform->SetScale(Math::Vector3{ 1.0f, 1.0f, 1.0f });
		auto* pModel = m_test3D.AddComponent<Renderings::Model3D>(iComponentManager);
		pModel->SetModelSourceName("Player");
		auto* pBoxCollider = m_test3D.AddComponent<Colliders::BoxCollider>(iComponentManager);
		pBoxCollider->SetPosition(Math::Vector3{ 0.0f, 1.0f, 0.0f });
		pBoxCollider->SetSize(Math::Vector3{ 1.0f, 2.0f, 1.0f });
		pBoxCollider->ApplyTransform();
		auto* pSphereCollider = m_test3D.AddComponent<Colliders::SphereCollider>(iComponentManager);
		pSphereCollider->SetPosition(Math::Vector3{ 0.0f, 1.0f, 0.0f });
		pSphereCollider->SetRadius(1.0f);
		pSphereCollider->ApplyTransform();
		// カメラにモデルを映す
		pModel->AddICameraScreen(*m_pCameraScreen);
		pBoxCollider->AddICameraScreen(*m_pCameraScreen);
		pSphereCollider->AddICameraScreen(*m_pCameraScreen);
	}

	{
		auto* pRectTransform = m_test2D.AddComponent<RectTransform>(iComponentManager);
		pRectTransform->SetAngle(-30.0f);
		auto* pImage = m_test2D.AddComponent<Renderings::Image>(iComponentManager);
		pImage->SetImageSourceName("DialogBox");
		pRectTransform->SetSize(pImage->GetSize() / 2.0f);
		auto* pText = m_test2D.AddComponent<Renderings::Text>(iComponentManager);
		pText->SetStr(L"あいうえお");
		pText->SetFontName(L"GenEi M Gothic v2");
		pText->SetFontSize(128.0f);
		pText->SetFontColor(DirectX::Colors::White);
		pText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pText->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		// キャンバスにUIを映す
		pImage->SetCanvas(*pCanvas);
		pText->SetCanvas(*pCanvas);
	}

	{
		auto* pRectTransform = m_test2D2.AddComponent<RectTransform>(iComponentManager);
		pRectTransform->SetAngle(45.0f);
		auto* pImage = m_test2D2.AddComponent<Renderings::Image>(iComponentManager);
		pImage->SetImageSourceName("DialogBox");
		pImage->SetOrderInLayer(1);
		pImage->SetColor(DirectX::Colors::Red);
		pRectTransform->SetSize(pImage->GetSize() / 2.0f);
		// キャンバスにUIを映す
		pImage->SetCanvas(*pCanvas);
	}

	{
		auto* pTransform = m_ground.AddComponent<Transform>(iComponentManager);
		pTransform->SetScale(Math::Vector3::One * 3.0f);
		auto* pModel = m_ground.AddComponent<Renderings::Model3D>(iComponentManager);
		pModel->SetModelSourceName("Ground");
		// カメラにモデルを映す
		pModel->AddICameraScreen(*m_pCameraScreen);
	}
}

// 更新処理
void SampleScene::Update(float elapsedTime)
{
	// 入力管理
	const auto& iInput = GetContext().GetIInput();

	// F5でシーン移動
	if (iInput.GetKeyDown(KeyName::F5))
	{
		GetContext().GetISceneManager().SetNextScene<SampleScene>();
		return;
	}

	m_test3D.Update(elapsedTime);
	m_test2D.Update(elapsedTime);

	// カメラの更新
	m_pDebugCamera->SetInput
	(
		iInput.GetMouseMovement(),
		iInput.GetMouseButton(MouseButtonName::Right),
		iInput.GetMouseButton(MouseButtonName::Middle),
		iInput.GetMouseWheelDelta()
	);
	m_camera.Update(elapsedTime);
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
		const Math::Vector2& outputSize = GetContext().GetIWindowController().GetOutputSize();
		// プロジェクション行列を設定
		m_pCameraScreen->SetProjectionMatrix(45.0f, outputSize);
		// キャンバスのサイズを設定
		m_canvas.GetComponent<Renderings::Canvas>()->SetSize(outputSize);
	}
}
