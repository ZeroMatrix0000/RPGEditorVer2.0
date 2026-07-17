/*
 * FileName:     BoxCollider.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/17
 *
 * 長方形の当たり判定
 */

#include "Pch.h"
#include "BoxCollider.h"

#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"
#include "../Renderings/ColliderRenderer.h"

// コンストラクタ
Colliders::BoxCollider::BoxCollider(const ComponentDesc& desc, Renderings::IColliderRenderer* pIColliderRenderer)
	: Component{ desc }
	, m_box{}
	, m_worldBox{}
	, m_color{ DirectX::Colors::LightGreen }
	, m_pICameraScreens{}
	, m_pIColliderRenderer{ pIColliderRenderer }
{
	// 描画者に長方形を追加
	m_pIColliderRenderer->AddPBoxCollider(this);
}

// デストラクタ
Colliders::BoxCollider::~BoxCollider()
{
	// 描画者から長方形を削除
	m_pIColliderRenderer->RemovePBoxCollider(this);
}

// 映るカメラ画面を追加
void Colliders::BoxCollider::AddICameraScreen(const Renderings::ICameraScreen& iCameraScreen)
{
	m_pICameraScreens.emplace(&iCameraScreen);
}

// 映るカメラ画面を削除
void Colliders::BoxCollider::RemoveICameraScreen(const Renderings::ICameraScreen& iCameraScreen)
{
	m_pICameraScreens.erase(&iCameraScreen);
}

// トランスフォームを適用
void Colliders::BoxCollider::ApplyTransform()
{
	// トランスフォームを取得
	const auto* pTransform = GetPOwner()->GetConstComponent<Transform>();
	// 取得できなければ何もしない
	if (!pTransform)
	{
		m_worldBox.position = m_box.position;
		m_worldBox.size = m_box.size;
		m_worldBox.rotation = Math::Quaternion::Identity;
		return;
	}

	// ワールド行列
	Math::Matrix world = pTransform->CreateWorldMatrix();

	m_worldBox.position = Math::Vector3::Transform(m_box.position, world);
	m_worldBox.size = m_box.size * pTransform->GetScale();
	m_worldBox.rotation = pTransform->GetRotation();
}
