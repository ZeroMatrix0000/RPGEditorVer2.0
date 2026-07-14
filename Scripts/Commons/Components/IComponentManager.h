/*
 * FileName:     IComponentManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * コンポーネント管理のインタフェース
 */

#pragma once

#include "Component.h"
#include "../Systems/OnlyOne.h"

namespace GameObjects
{
	class GameObject;
}

namespace Components
{
	class ComponentCreatePermit;

	// コンポーネント管理のインタフェース
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
		std::unique_ptr<Component> Create(GameObject* pOwner = nullptr)
		{
			return Create(typeid(TComponent), pOwner);
		};
		// コンポーネントを作成（特殊化）
		template<typename TComponent> requires
			IsDerived<TComponent, Component> &&
			std::constructible_from<TComponent, const ComponentCreatePermit&, GameObject*>
		std::unique_ptr<Component> Create(GameObject* pOwner = nullptr)
		{
			RegisterCreate
			(
				typeid(TComponent),
				[](const ComponentCreatePermit& permit, GameObject* pOwner)
				{
					return std::make_unique<TComponent>(permit, pOwner);
				}
			);
			return Create(typeid(TComponent), pOwner);
		};

		// 未参照コンポーネントを取得
		template<typename TComponent> requires IsDerived<TComponent, Component>
		TComponent* GetNullReferences()
		{
			return static_cast<TComponent*>(GetNullReferences(typeid(TComponent)));
		}



	private:


		/* メンバ関数 */

		// コンポーネントを作成
		virtual std::unique_ptr<Component> Create(const std::type_index& index, GameObject* pOwner) = 0;

		// コンポーネント作成関数を追加
		virtual void RegisterCreate
		(
			const std::type_index& index,
			const std::function<std::unique_ptr<Component>(ComponentCreatePermit, GameObject*)>& CreateComponent
		) = 0;

		// 未参照コンポーネントを取得
		virtual Component* GetNullReferences(const std::type_index& index) = 0;


	};
}
