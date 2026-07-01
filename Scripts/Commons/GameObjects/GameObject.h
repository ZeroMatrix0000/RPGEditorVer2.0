/*
 * FileName:     GameObject.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
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

		// コンポーネントを追加
		template<typename TComponent> requires IsDerived<TComponent, Component>
		TComponent* AddComponent(const ComponentFactory& componentFactory)
		{
			m_components.emplace(typeid(TComponent), componentFactory.Create<TComponent>(this));
			return dynamic_cast<TComponent*>(m_components.at(typeid(TComponent)).get());
		}


	private:


		/* メンバ変数 */

		// コンポーネント
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

	};
}
