/*
 * FileName:     ComponentManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * コンポーネント管理
 */

#pragma once

#include "IComponentManager.h"
#include "ComponentCreatePermit.h"

namespace GameObjects
{
	// コンポーネント管理
	class ComponentManager : public IComponentManager
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ComponentManager();

		// コンポーネントを作成
		std::unique_ptr<Component> Create(const std::type_index& index, GameObject* pOwner) const override;

		// コンポーネントを追加
		template<typename TComponent> requires IsDerived<TComponent, Component>
		void AddComponent(const std::function<std::unique_ptr<Component>(ComponentCreatePermit, GameObject*)>& CreateComponent)
		{
			m_CreateComponentList.emplace(typeid(TComponent), CreateComponent);
		}
		// コンポーネントを追加
		template<typename TComponent> requires IsDerived<TComponent, Component>
		void AddComponent()
		{
			m_CreateComponentList.emplace
			(
				typeid(TComponent),
				[&](ComponentCreatePermit permit, GameObject* pOwner)
				{
					return std::make_unique<TComponent>(permit, pOwner);
				}
			);
		}


		/* メンバ変数 */

		// コンポーネント作成許可証
		ComponentCreatePermit m_permit;

		// コンポーネント作成関数
		std::unordered_map<std::type_index, std::function<std::unique_ptr<Component>(ComponentCreatePermit, GameObject*)>> m_CreateComponentList;

	};
}
