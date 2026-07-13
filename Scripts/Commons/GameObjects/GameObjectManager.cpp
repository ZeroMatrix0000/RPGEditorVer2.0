/*
 * FileName:     GameObjectManager.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * ゲームオブジェクト管理
 */

#include "Pch.h"
#include "GameObjectManager.h"

#include "GameObject.h"
#include "../Systems/IResources.h"

// コンストラクタ
GameObjects::GameObjectManager::GameObjectManager(const Systems::IResources& iResources)
	: IGameObjectManager{}
	, m_AddComponentList{}
	, m_refIResources{ iResources }
{
}

// ゲームオブジェクトを読み込む
void GameObjects::GameObjectManager::Load
(
	const IComponentManager& iComponentManager,
	const std::string& jsonName,
	std::unordered_map<std::string, std::unique_ptr<GameObject>>* pGameObjects
) const
{
	if (!pGameObjects)
	{
		return;
	}
	pGameObjects->clear();

	// Json
	const auto* json = m_refIResources.GetJson(jsonName);
	if (!json)
	{
		return;
	}

	// 要素ごとにループ
	for (const auto& element : json->items())
	{
		// 文字列型ならPrefabから生成
		if (element.value().is_string())
		{
			// Json
			const auto* newJson = m_refIResources.GetJson(element.value());
			if (!newJson)
			{
				continue;
			}
			std::unique_ptr<GameObject> gameObject = Create(iComponentManager, element.value());
			if (gameObject)
			{
				pGameObjects->emplace(element.key(), std::move(gameObject));
			}
		}
		else
		{
			std::unique_ptr<GameObject> gameObject = Create(iComponentManager, element.value());
			if (gameObject)
			{
				pGameObjects->emplace(element.key(), std::move(gameObject));
			}
		}
	}
}

// ゲームオブジェクトを作成
std::unique_ptr<GameObject> GameObjects::GameObjectManager::Create(const IComponentManager& iComponentManager, const nlohmann::ordered_json& json) const
{
	std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>();
	for (const auto& element : json.items())
	{
		auto* component = m_AddComponentList.at(element.key())(iComponentManager, gameObject.get());
		component->Initalize(element.value());
	}
	return gameObject;
}
