/*
 * FileName:     ComponentManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
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

		// コンポーネント作成関数を追加
		template<typename TComponent> requires IsDerived<TComponent, Component>
		void RegisterCreate(const std::function<std::unique_ptr<Component>(ComponentCreatePermit, GameObject*)>& CreateComponent)
		{
			m_CreateComponentList.emplace(typeid(TComponent), CreateComponent);
		}


	private:


		/* メンバ関数 */

		// コンポーネントを作成
		std::unique_ptr<Component> Create(const std::type_index& index, GameObject* pOwner) const override;


		/* メンバ変数 */

		// コンポーネント作成許可証
		ComponentCreatePermit m_permit;

		// コンポーネント作成関数
		std::unordered_map<std::type_index, std::function<std::unique_ptr<Component>(ComponentCreatePermit, GameObject*)>> m_CreateComponentList;

	};
}
