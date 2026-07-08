/*
 * FileName:     IComponentManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * コンポーネント工場
 */

#pragma once

#include "Component.h"
#include "../Systems/OnlyOne.h"

namespace GameObjects
{
	class GameObject;

	// コンポーネント工場
	class IComponentManager : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		IComponentManager()
			: OnlyOne{ typeid(IComponentManager) }
		{
		}

		// コンポーネントを作成
		template<typename TComponent> requires IsDerived<TComponent, Component>
		std::unique_ptr<Component> Create(GameObject* pOwner = nullptr) const
		{
			return Create(typeid(TComponent), pOwner);
		};

		// コンポーネントを作成
		virtual std::unique_ptr<Component> Create(const std::type_index& index, GameObject* pOwner) const = 0;

	};
}
