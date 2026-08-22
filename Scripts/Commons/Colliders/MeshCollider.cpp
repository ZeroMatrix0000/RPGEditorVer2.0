/*
 * FileName:     MeshCollider.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/22
 *
 * メッシュの当たり判定
 */

#include "Pch.h"
#include "MeshCollider.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/IGameObjectFinder.h"
#include "../Components/Transform.h"
#include "../Renderings/ColliderRenderer.h"
#include "../Renderings/ICameraScreen.h"
#include "../Systems/IResources.h"
#include "../Systems/JsonSerializer.h"

// コンストラクタ
Colliders::MeshCollider::MeshCollider(const ComponentDesc& desc, Renderings::IColliderRenderer* pIColliderRenderer, const Systems::IResources& iResources)
	: Component{ desc }
	, m_meshName{}
	, m_color{ DirectX::Colors::LightGreen }
	, m_worldMesh{}
	, m_pTransform{ GetPOwner()->GetNullReferences<Transform>() }
	, m_pICameraScreens{}
	, m_pIColliderRenderer{ pIColliderRenderer }
	, m_refIResources{ iResources }
{
	// 描画者に長方形を追加
	m_pIColliderRenderer->AddPMeshCollider(this);
}

// デストラクタ
Colliders::MeshCollider::~MeshCollider()
{
	// 描画者から長方形を削除
	m_pIColliderRenderer->RemovePMeshCollider(this);
}

// 初期化処理
void Colliders::MeshCollider::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	m_pTransform = GetPOwner()->GetComponent<Transform>();

	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_meshName, "MeshName");
	serializer.AddParameter(&m_color, "Color");
	serializer.AddParameter(&m_pICameraScreens, "CameraScreens");
	serializer.Load(json);
}

// 映るカメラ画面を追加
void Colliders::MeshCollider::AddICameraScreen(const Renderings::ICameraScreen& iCameraScreen)
{
	if (std::ranges::find(m_pICameraScreens, &iCameraScreen) == m_pICameraScreens.end())
	{
		m_pICameraScreens.push_back(&iCameraScreen);
	}
}

// 映るカメラ画面を削除
void Colliders::MeshCollider::RemoveICameraScreen(const Renderings::ICameraScreen& iCameraScreen)
{
	auto it = std::ranges::find(m_pICameraScreens, &iCameraScreen);
	if (it != m_pICameraScreens.end())
	{
		m_pICameraScreens.erase(it);
	}
}

// トランスフォームを適用
void Colliders::MeshCollider::ApplyTransform()
{
	const auto* pMesh = m_refIResources.GetMesh(m_meshName);

	if (!pMesh)
	{
		return;
	}

	m_worldMesh = *pMesh;
	m_worldMesh.ApplyMatrix(m_pTransform->CreateWorldMatrix());
}
