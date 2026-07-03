/*
 * FileName:     ComponentFactory.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * コンポーネント工場
 */

#pragma once

#include "../Systems/OnlyOne.h"
#include "../Renderings/Model3D.h"
#include "../Renderings/CameraScreen.h"
#include "ComponentCreatePermit.h"
#include "Transform.h"

// 前方宣言
namespace Renderings
{
	class IModel3DRenderer;
}

namespace GameObjects
{
	// 前方宣言
	class Component;
	class GameObject;

	class ComponentFactory : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ComponentFactory();

		// モデル描画インタフェースのポインタを設定
		void SetPIModelRenderer(Renderings::IModel3DRenderer* pIModelRenderer) { m_pIModelRenderer = pIModelRenderer; }

		// コンポーネントを作成
		template<typename TComponent> requires IsDerived<TComponent, Component>
		std::unique_ptr<TComponent> Create(GameObject* pOwner = nullptr) const { return std::make_unique<TComponent>(m_permit, pOwner); };


		/* メンバ変数 */

		// コンポーネント作成許可証
		ComponentCreatePermit m_permit;

		// モデル描画インタフェースのポインタ
		Renderings::IModel3DRenderer* m_pIModelRenderer;

	};

	// 3Dモデルコンポーネントを作成
	template<>
	inline std::unique_ptr<Renderings::Model3D> ComponentFactory::Create(GameObject* pOwner) const
	{
		return std::make_unique<Renderings::Model3D>(m_permit, pOwner, m_pIModelRenderer);
	}
}
