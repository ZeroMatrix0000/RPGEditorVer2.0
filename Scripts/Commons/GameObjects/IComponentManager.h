/*
 * FileName:     IComponentManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * コンポーネント管理のインタフェース
 */

#pragma once

#include "Component.h"
#include "../Systems/OnlyOne.h"

namespace GameObjects
{
	class GameObject;
	class ComponentCreatePermit;

	// コンポーネント管理のインタフェース
	class IComponentManager : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		IComponentManager(const ComponentCreatePermit& permit)
			: OnlyOne{ typeid(IComponentManager) }
			, m_refPermit{ permit }
		{
		}

		// コンポーネントを作成
		template<typename TComponent> requires IsDerived<TComponent, Component>
		std::unique_ptr<Component> Create(GameObject* pOwner = nullptr) const
		{
			return Create(typeid(TComponent), pOwner);
		};
		// コンポーネントを作成（特殊化）
		template<typename TComponent> requires
			IsDerived<TComponent, Component> &&
			std::constructible_from<TComponent, const ComponentCreatePermit&, GameObject*>
		std::unique_ptr<Component> Create(GameObject* pOwner = nullptr) const
		{
			return std::make_unique<TComponent>(m_refPermit, pOwner);
		};



	private:


		/* メンバ関数 */

		// コンポーネントを作成
		virtual std::unique_ptr<Component> Create(const std::type_index& index, GameObject* pOwner) const = 0;


		/* メンバ変数 */

		// コンポーネント作成許可証の参照
		const ComponentCreatePermit& m_refPermit;

	};
}
