/*
 * FileName:     MeshCollider.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
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

// コンストラクタ
Colliders::MeshCollider::MeshCollider(const ComponentDesc& desc, Renderings::IColliderRenderer* pIColliderRenderer, const Systems::IResources& iResources)
	: Component{ desc }
	, m_worldMesh{}
	, m_color{ DirectX::Colors::LightGreen }
	, m_pMesh{}
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

	// 要素ごとにループ
	for (const auto& element : json.items())
	{
		const std::string& key = element.key();
		if (key == "MeshName")
		{
			SetMesh(element.value().get<std::string>());
		}
		else if (key == "Color")
		{
			SetColor(JsonSerializer::Json2Color(element.value()));
		}
		else if (key == "CameraScreen")
		{
			for (const auto& cameraScreen : element.value())
			{
				GameObject* pObj = pIGameObjectFinder->Find(cameraScreen.get<std::string>());
				AddICameraScreen(*pObj->GetComponent<Renderings::ICameraScreen>());
			}
		}
		else
		{
			Utility::Throw();
		}
	}
}

// メッシュを設定
void Colliders::MeshCollider::SetMesh(const std::string& meshName)
{
	m_pMesh = m_refIResources.GetMesh(meshName);
}

// 映るカメラ画面を追加
void Colliders::MeshCollider::AddICameraScreen(const Renderings::ICameraScreen& iCameraScreen)
{
	m_pICameraScreens.emplace(&iCameraScreen);
}

// 映るカメラ画面を削除
void Colliders::MeshCollider::RemoveICameraScreen(const Renderings::ICameraScreen& iCameraScreen)
{
	m_pICameraScreens.erase(&iCameraScreen);
}

// トランスフォームを適用
void Colliders::MeshCollider::ApplyTransform()
{
	if (!m_pMesh)
	{
		return;
	}

	m_worldMesh = *m_pMesh;
	m_worldMesh.ApplyMatrix(m_pTransform->CreateWorldMatrix());
}
