/*
 * FileName:     ComponentFactory.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * コンポーネント工場
 */

#pragma once

#include "../Systems/OnlyOne.h"
#include "../Renderings/CameraScreen.h"
#include "../Renderings/Image.h"
#include "ComponentCreatePermit.h"
#include "Transform.h"

namespace Renderings
{
	class IModel3DRenderer;
	class IImageRenderer;
}

namespace GameObjects
{
	class Component;
	class GameObject;

	// コンポーネント工場
	class ComponentFactory : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ComponentFactory();

		// モデル描画インタフェースのポインタを設定
		void SetPIModelRenderer(Renderings::IModel3DRenderer* pIModelRenderer) { m_pIModelRenderer = pIModelRenderer; }
		// 画像描画インタフェースのポインタを設定
		void SetPIImageRenderer(Renderings::IImageRenderer* pIImageRenderer) { m_pIImageRenderer = pIImageRenderer; }

		// コンポーネントを作成
		template<typename TComponent> requires IsDerived<TComponent, Component>
		std::unique_ptr<TComponent> Create(GameObject* pOwner = nullptr) const { return std::make_unique<TComponent>(m_permit, pOwner); };


		/* メンバ変数 */

		// コンポーネント作成許可証
		ComponentCreatePermit m_permit;

		// モデル描画インタフェースのポインタ
		Renderings::IModel3DRenderer* m_pIModelRenderer;
		// 画像描画インタフェースのポインタ
		Renderings::IImageRenderer* m_pIImageRenderer;

	};

	// カメラコンポーネントを作成
	template<>
	inline std::unique_ptr<Renderings::CameraScreen<Camera::EulerCamera>> ComponentFactory::Create(GameObject* pOwner) const
	{
		return std::make_unique<Renderings::CameraScreen<Camera::EulerCamera>>(m_permit, pOwner, m_pIModelRenderer);
	}
	// カメラコンポーネントを作成
	template<>
	inline std::unique_ptr<Renderings::CameraScreen<Camera::EulerTargetCamera>> ComponentFactory::Create(GameObject* pOwner) const
	{
		return std::make_unique<Renderings::CameraScreen<Camera::EulerTargetCamera>>(m_permit, pOwner, m_pIModelRenderer);
	}
	// カメラコンポーネントを作成
	template<>
	inline std::unique_ptr<Renderings::CameraScreen<Camera::QuaternionCamera>> ComponentFactory::Create(GameObject* pOwner) const
	{
		return std::make_unique<Renderings::CameraScreen<Camera::QuaternionCamera>>(m_permit, pOwner, m_pIModelRenderer);
	}
	// カメラコンポーネントを作成
	template<>
	inline std::unique_ptr<Renderings::CameraScreen<Camera::QuaternionTargetCamera>> ComponentFactory::Create(GameObject* pOwner) const
	{
		return std::make_unique<Renderings::CameraScreen<Camera::QuaternionTargetCamera>>(m_permit, pOwner, m_pIModelRenderer);
	}

	// 画像コンポーネントを作成
	template<>
	inline std::unique_ptr<Renderings::Image> ComponentFactory::Create(GameObject* pOwner) const
	{
		return std::make_unique<Renderings::Image>(m_permit, pOwner, m_pIImageRenderer);
	}
}
