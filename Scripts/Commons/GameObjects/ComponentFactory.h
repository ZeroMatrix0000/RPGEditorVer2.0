/*
 * FileName:     ComponentFactory.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * コンポーネント工場
 */

#pragma once

#include "../Systems/OnlyOne.h"
#include "../Renderings/Model3D.h"
#include "ComponentCreatePermit.h"
#include "Transform.h"

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
		ComponentFactory()
			: OnlyOne{ typeid(ComponentFactory) }
			, m_permit{}
		{
		}

		// コンポーネントを作成
		template<typename TComponent> requires IsDerived<TComponent, Component>
		std::unique_ptr<TComponent> Create(GameObject* pOwner = nullptr) const { return nullptr; };


		/* メンバ変数 */

		// コンポーネント作成許可証
		ComponentCreatePermit m_permit;

	};

	// トランスフォームコンポーネントを作成
	template<>
	inline std::unique_ptr<Transform> ComponentFactory::Create(GameObject*) const
	{
		return std::make_unique<Transform>(m_permit);
	}
	// 3Dモデルコンポーネントを作成
	template<>
	inline std::unique_ptr<Renderings::Model3D> ComponentFactory::Create(GameObject* pOwner) const
	{
		return std::make_unique<Renderings::Model3D>(m_permit, pOwner);
	}
}
