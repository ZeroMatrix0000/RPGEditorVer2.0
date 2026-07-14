/*
 * FileName:     GameObject.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * ゲームオブジェクト
 */

#pragma once

#include "../Components/IComponentManager.h"

namespace Components
{
	class Component;
}

namespace GameObjects
{

	// ゲームオブジェクト
	class GameObject
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		GameObject(IComponentManager* pIComponentManager);

		// 更新処理
		void Update(float elapsedTime);

		// 名前を設定
		void SetName(const std::string& name) { m_name = name; }

		// 名前を取得
		const std::string& GetName() const { return m_name; }

		// コンポーネントを取得
		template<typename TComponent> requires IsDerived<TComponent, Component>
		TComponent* GetComponent()
		{
			auto it = m_components.find(typeid(TComponent));
			if (it == m_components.end())
			{
				return m_pIComponentManager->GetNullReferences<TComponent>();
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
				return m_pIComponentManager->GetNullReferences<TComponent>();
			}
			return static_cast<TComponent*>(it->second.get());
		}

		// コンポーネントを追加
		template<typename TComponent> requires IsDerived<TComponent, Component>
		TComponent* AddComponent()
		{
			m_components.emplace(typeid(TComponent), m_pIComponentManager->Create<TComponent>(this));
			return GetComponent<TComponent>();
		}


	private:


		/* メンバ変数 */

		// 名前
		std::string m_name;

		// コンポーネント
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

		// コンポーネント管理のポインタ
		IComponentManager* m_pIComponentManager;

	};
}
