/*
 * FileName:     GameObjectManager.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * ゲームオブジェクト管理
 */

#include "Pch.h"
#include "GameObjectManager.h"

#include "GameObject.h"
#include "../Systems/IResources.h"
#include "../Systems/IErrorMessage.h"

// コンストラクタ
GameObjects::GameObjectManager::GameObjectManager(const Systems::IResources& iResources)
	: IGameObjectManager{}
	, m_AddComponentList{}
	, m_nullReference{}
	, m_pIComponentManager{}
	, m_refIResources{ iResources }
{
}

// 初期化処理
void GameObjects::GameObjectManager::Initialize(IComponentManager* pIComponentManager)
{
	m_nullReference = std::make_unique<GameObject>(pIComponentManager);
	m_pIComponentManager = pIComponentManager;
}

// ゲームオブジェクトを読み込む
void GameObjects::GameObjectManager::Load
(
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
			std::unique_ptr<GameObject> gameObject = Create(element.value());
			if (gameObject)
			{
				pGameObjects->emplace(element.key(), std::move(gameObject));
			}
		}
		else
		{
			std::unique_ptr<GameObject> gameObject = Create(element.value());
			if (gameObject)
			{
				pGameObjects->emplace(element.key(), std::move(gameObject));
			}
		}
	}
}

// ゲームオブジェクトを名前で検索
GameObject* GameObjects::GameObjectManager::FindGameObject
(
	const std::string& name,
	const std::unordered_map<std::string, std::unique_ptr<GameObject>>& gameObjects
) const
{
	auto it = gameObjects.find(name);
	if (it == gameObjects.end())
	{
		// エラーメッセージを追加
		Systems::IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
		(
			L"ゲームオブジェクトが見つかりません。 | name: %s",
			Utility::string2wstring(name).c_str()
		));
		return m_nullReference.get();
	}
	else
	{
		return it->second.get();
	}
}

// ゲームオブジェクトを作成
std::unique_ptr<GameObject> GameObjects::GameObjectManager::Create(const nlohmann::ordered_json& json) const
{
	std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>(m_pIComponentManager);
	for (const auto& element : json.items())
	{
		// コンポーネント追加関数
		auto it = m_AddComponentList.find(element.key());
		if (it == m_AddComponentList.end())
		{
			// エラーメッセージを追加
			Systems::IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
			(
				L"不明なコンポーネントです。 | name: %s",
				Utility::string2wstring(element.key()).c_str()
			));
			continue;
		}
		// コンポーネントを追加
		auto* component = it->second(gameObject.get());
		component->Initalize(element.value());
	}
	return gameObject;
}
