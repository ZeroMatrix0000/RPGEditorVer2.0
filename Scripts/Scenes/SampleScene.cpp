/*
 * FileName:     SampleScene.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
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

// コンストラクタ
SampleScene::SampleScene(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Scene{ permit, pOwner }
	, m_test3D{}
	, m_test2D{}
	, m_test2D2{}
	, m_camera{}
	, m_canvas{}
{
}

// 初期化処理
void SampleScene::Initialize(const SceneTransitionData& data)
{
	// 出力サイズ
	const Math::Vector2& outputSize = GetContext().GetIWindowController().GetOutputSize();

	// コンポーネント工場
	const auto& componentFactory = GetContext().GetComponentFactory();

	auto* pTransform = m_test3D.AddComponent<Transform>(componentFactory);
	pTransform->SetPosition(Math::Vector3::Left * 5.0f);
	pTransform->SetRotation(Math::Euler{ 0.0f, 45.0f, 0.0f }.CreateQuaternion());
	pTransform->SetScale(Math::Vector3{ 2.0f, 3.0f, 1.0f });
	auto* pModel = m_test3D.AddComponent<Renderings::Model3D>(componentFactory);
	pModel->SetModelSourceName("Player");

	auto* pRectTransform = m_test2D.AddComponent<RectTransform>(componentFactory);
	pRectTransform->SetPivot(Utility::AlignmentPoint::MiddleCenter);
	pRectTransform->SetAnchor(Utility::AlignmentPoint::MiddleCenter);
	pRectTransform->SetAngle(-30.0f);
	auto* pImage = m_test2D.AddComponent<Renderings::Image>(componentFactory);
	pImage->SetImageSourceName("DialogBoxUI");
	pRectTransform->SetSize(pImage->GetSize() / 2.0f);
	auto* pText = m_test2D.AddComponent<Renderings::Text>(componentFactory);
	pText->SetStr(L"テスト");
	pText->SetFontName(L"GenEi M Gothic v2");
	pText->SetFontSize(128.0f);
	pText->SetFontColor(DirectX::Colors::White);
	pText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pText->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	auto* pRectTransform2 = m_test2D2.AddComponent<RectTransform>(componentFactory);
	pRectTransform2->SetPivot(Utility::AlignmentPoint::MiddleCenter);
	pRectTransform2->SetAnchor(Utility::AlignmentPoint::MiddleCenter);
	pRectTransform2->SetAngle(45.0f);
	auto* pImage2 = m_test2D2.AddComponent<Renderings::Image>(componentFactory);
	pImage2->SetImageSourceName("DialogBoxUI");
	pImage2->SetOrderInLayer(1);
	pImage2->SetColor(DirectX::Colors::Red);
	pRectTransform2->SetSize(pImage2->GetSize() / 2.0f);

	auto* cameraScreen = m_camera.AddComponent<Renderings::CameraScreen<Camera::EulerTargetCamera>>(componentFactory);
	cameraScreen->SetCamera(Camera::EulerTargetCamera{ Math::Vector3::Zero, Math::Euler{ -30.0f, 0.0f, 0.0f }, 15.0f });
	cameraScreen->SetProjectionMatrix(45.0f, outputSize);

	auto* canvas = m_canvas.AddComponent<Renderings::Canvas>(componentFactory);
	canvas->Initialize(Renderings::Canvas::FixedSize::Vertical, outputSize);

	// カメラにモデルを映す
	cameraScreen->AddModel(*pModel);

	// キャンバスにUIを映す
	pImage->SetCanvas(*canvas);
	pText->SetCanvas(*canvas);
	pImage2->SetCanvas(*canvas);
}

// 更新処理
void SampleScene::Update(float elapsedTime)
{
	m_test3D.Update(elapsedTime);
	m_test2D.Update(elapsedTime);

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
		// キャンバスのサイズを設定
		m_canvas.GetComponent<Renderings::Canvas>()->SetSize(outputSize);
	}
}
