/*
 * FileName:     GameObjectManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * ゲームオブジェクト管理
 */

#pragma once

#include "IGameObjectManager.h"
#include "GameObject.h"

namespace Systems
{
	class IResources;
}

namespace GameObjects
{
	// ゲームオブジェクト管理
	class GameObjectManager : public IGameObjectManager
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		GameObjectManager(const Systems::IResources& iResources);

		// 初期化処理
		void Initialize(IComponentManager* pIComponentManager);

		// コンポーネントを追加関数を追加
		template<typename TComponent> requires IsDerived<TComponent, Component>
		void RegisterAdd(const std::string& componentName)
		{
			m_AddComponentList.emplace
			(
				componentName,
				[](GameObject* pOwner)
				{
					return pOwner->AddComponent<TComponent>();
				}
			);
		}

		// ゲームオブジェクトを読み込む
		void Load
		(
			const std::string& jsonName,
			std::unordered_map<std::string, std::unique_ptr<GameObject>>* pGameObjects
		) const override;

		// ゲームオブジェクトを名前で検索
		GameObject* FindGameObject
		(
			const std::string& name,
			const std::unordered_map<std::string, std::unique_ptr<GameObject>>& gameObjects
		) const override;


	private:


		/* メンバ関数 */

		// ゲームオブジェクトを作成
		std::unique_ptr<GameObject> Create(const nlohmann::ordered_json& json) const;


		/* メンバ変数 */

		// コンポーネント追加関数
		std::unordered_map<std::string, std::function<Component*(GameObject*)>> m_AddComponentList;

		// 未参照ゲームオブジェクト
		std::unique_ptr<GameObject> m_nullReference;

		// コンポーネント管理のポインタ
		IComponentManager* m_pIComponentManager;

		// リソースのインタフェースの参照
		const Systems::IResources& m_refIResources;

	};
}
