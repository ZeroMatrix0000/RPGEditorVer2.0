/*
 * FileName:     SphereCollider.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * 球の当たり判定
 */

#include "Pch.h"
#include "SphereCollider.h"

#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"
#include "../Renderings/ColliderRenderer.h"

// コンストラクタ
Colliders::SphereCollider::SphereCollider(const ComponentCreatePermit& permit, GameObject* pOwner, Renderings::IColliderRenderer* pIColliderRenderer)
	: Component{ permit, pOwner }
	, m_sphere{}
	, m_worldSphere{}
	, m_color{ DirectX::Colors::LightGreen }
	, m_pICameraScreens{}
	, m_pIColliderRenderer{ pIColliderRenderer }
{
	// 描画者に球を追加
	m_pIColliderRenderer->AddPSphereCollider(this);
}

// デストラクタ
Colliders::SphereCollider::~SphereCollider()
{
	// 描画者から長方形を削除
	m_pIColliderRenderer->RemovePSphereCollider(this);
}

// 映るカメラ画面を追加
void Colliders::SphereCollider::AddICameraScreen(const Renderings::ICameraScreen& iCameraScreen)
{
	m_pICameraScreens.emplace(&iCameraScreen);
}

// 映るカメラ画面を削除
void Colliders::SphereCollider::RemoveICameraScreen(const Renderings::ICameraScreen& iCameraScreen)
{
	m_pICameraScreens.erase(&iCameraScreen);
}

// トランスフォームを適用
void Colliders::SphereCollider::ApplyTransform()
{
	// トランスフォームを取得
	const auto* pTransform = GetPOwner()->GetConstComponent<Transform>();
	// 取得できなければ何もしない
	if (!pTransform)
	{
		m_worldSphere = m_sphere;
		return;
	}

	// ワールド行列
	Math::Matrix world = pTransform->CreateWorldMatrix();
	// 拡大
	Math::Vector3 scale = pTransform->GetScale();

	m_worldSphere.centerPosition = Math::Vector3::Transform(m_sphere.centerPosition, world);
	m_worldSphere.radius = m_sphere.radius * Math::Max(scale.x, scale.y, scale.z);
}
