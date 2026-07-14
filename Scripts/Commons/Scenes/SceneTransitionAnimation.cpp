/*
 * FileName:     SceneTransitionAnimation.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * シーン遷移時のアニメーション
 */

#include "Pch.h"
#include "SceneTransitionAnimation.h"

#include "../Renderings/Canvas.h"
#include "../Renderings/Image.h"
#include "../GameObjects/GameObject.h"
#include "../Components/RectTransform.h"
#include "../Components/IComponentManager.h"

// コンストラクタ
Scenes::SceneTransitionAnimation::SceneTransitionAnimation()
	: m_changingRate{}
	, m_image{}
	, m_imageRectTransform{}
	, m_canvas{}
{
}

// 初期化処理
void Scenes::SceneTransitionAnimation::Initialize(const Math::Vector2& outputSize, IComponentManager* pIComponentManager)
{
	// アニメーションの設定
	SetAnimation(false);

	// 画像の設定
	m_image = std::make_unique<GameObject>(pIComponentManager);
	m_imageRectTransform = m_image->AddComponent<RectTransform>();
	m_imageRectTransform->SetAngle(CHANGE_ANGLE);
	auto* pImage = m_image->AddComponent<Renderings::Image>();
	pImage->SetImageSourceName("Box");
	pImage->SetColor(DirectX::Colors::Black);
	pImage->SetOrderInLayer(32767);
	// キャンバスの設定
	m_canvas = std::make_unique<GameObject>(pIComponentManager);
	auto* pCanvas = m_canvas->AddComponent<Renderings::Canvas>();
	pCanvas->Initialize(Renderings::Canvas::FixedSize::None, outputSize);

	// キャンバスに画像を映す
	pImage->SetCanvas(*pCanvas);

	// 長方形サイズの設定
	m_imageRectTransform->SetSize(Math::Vector2
	{
		Math::Abs(outputSize.x * Math::Cos(Math::Deg2Rad(CHANGE_ANGLE))) + Math::Abs(outputSize.y * Math::Sin(Math::Deg2Rad(CHANGE_ANGLE))),
		Math::Abs(outputSize.x * Math::Sin(Math::Deg2Rad(CHANGE_ANGLE))) + Math::Abs(outputSize.y * Math::Cos(Math::Deg2Rad(CHANGE_ANGLE)))
	});
}

// 更新処理
void Scenes::SceneTransitionAnimation::Update(float elapsedTime)
{
	// 切り替え率を更新
	m_changingRate.Tick(elapsedTime);

	// 移動方向
	Math::Vector2 direction = Math::Vector2{ Math::Cos(Math::Deg2Rad(CHANGE_ANGLE)), Math::Sin(Math::Deg2Rad(CHANGE_ANGLE)) } * m_imageRectTransform->GetRect().size.x;
	// 長方形座標の設定
	m_imageRectTransform->SetPosition(direction * m_changingRate.GetMovement());
}

// キャンバスサイズの変更
void Scenes::SceneTransitionAnimation::SetCanvasSize(const Math::Vector2& outputSize)
{
	m_canvas->GetComponent<Renderings::Canvas>()->SetSize(outputSize);

	// 長方形サイズの設定
	m_imageRectTransform->SetSize(Math::Vector2
	{
		Math::Abs(outputSize.x * Math::Cos(Math::Deg2Rad(CHANGE_ANGLE))) + Math::Abs(outputSize.y * Math::Sin(Math::Deg2Rad(CHANGE_ANGLE))),
		Math::Abs(outputSize.x * Math::Sin(Math::Deg2Rad(CHANGE_ANGLE))) + Math::Abs(outputSize.y * Math::Cos(Math::Deg2Rad(CHANGE_ANGLE)))
	});

	// 移動方向
	Math::Vector2 direction = Math::Vector2
	{
		Math::Cos(Math::Deg2Rad(CHANGE_ANGLE)),
		Math::Sin(Math::Deg2Rad(CHANGE_ANGLE))
	} * m_imageRectTransform->GetRect().size.x;
	// 長方形座標の設定
	m_imageRectTransform->SetPosition(direction* m_changingRate.GetMovement());
}

// 切り替え率を設定
void Scenes::SceneTransitionAnimation::SetAnimation(bool isEnter)
{
	m_changingRate.SetMovement
	(
		isEnter ? -1.0f : 0.0f,
		isEnter ? 0.0f : 1.0f,
		CHANGE_TIME,
		Easing::Type::Quart,
		isEnter ? Easing::InOut::Out : Easing::InOut::In
	);
}
