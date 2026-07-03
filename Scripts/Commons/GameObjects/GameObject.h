/*
 * FileName:     GameObject.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * ゲームオブジェクト
 */

#pragma once

#include "ComponentFactory.h"

namespace GameObjects
{
	// 前方宣言
	class Component;

	class GameObject
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		GameObject();

		// 更新処理
		void Update(float elapsedTime);

		// コンポーネントを取得
		template<typename TComponent> requires IsDerived<TComponent, Component>
		TComponent* GetComponent()
		{
			auto it = m_components.find(typeid(TComponent));
			if (it == m_components.end())
			{
				return nullptr;
			}
			return static_cast<TComponent*>(it->second.get());
		}
		// 変更不可コンポーネントを取得
		template<typename TComponent> requires IsDerived<TComponent, Component>
		const TComponent* GetConstComponent() const
		{
			auto it = m_components.find(typeid(TComponent));
			if (it == m_components.end())
			{
				return nullptr;
			}
			return static_cast<TComponent*>(it->second.get());
		}

		// コンポーネントを追加
		template<typename TComponent> requires IsDerived<TComponent, Component>
		TComponent* AddComponent(const ComponentFactory& componentFactory)
		{
			m_components.emplace(typeid(TComponent), componentFactory.Create<TComponent>(this));
			return GetComponent<TComponent>();
		}


	private:


		/* メンバ変数 */

		// コンポーネント
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

	};
}
