/*
 * FileName:     SphereCollider.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/22
 *
 * 球の当たり判定
 */

#include "Pch.h"
#include "SphereCollider.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/IGameObjectFinder.h"
#include "../Components/Transform.h"
#include "../Renderings/ColliderRenderer.h"
#include "../Renderings/ICameraScreen.h"

// コンストラクタ
Colliders::SphereCollider::SphereCollider(const ComponentDesc& desc, Renderings::IColliderRenderer* pIColliderRenderer)
	: Component{ desc }
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

// 初期化処理
void Colliders::SphereCollider::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	// 要素ごとにループ
	for (const auto& element : json.items())
	{
		const std::string& key = element.key();
		if (key == "Position")
		{
			SetPosition(JsonSerializer::Json2Vector3(element.value()));
		}
		else if (key == "Radius")
		{
			SetRadius(element.value().get<float>());
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
