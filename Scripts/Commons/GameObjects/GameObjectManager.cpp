/*
 * FileName:     GameObjectManager.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
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
	, m_pGameObjects{}
	, m_dontDestroyOnLoadGameObjects{}
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

// 管理するゲームオブジェクトのポインタを設定
void GameObjects::GameObjectManager::SetPGameObjects(std::vector<std::unique_ptr<GameObject>>* pGameObjects)
{
	m_pGameObjects = pGameObjects;
}

// ゲームオブジェクトを読み込む
void GameObjects::GameObjectManager::Load(const std::string& jsonName)
{
	// Json
	const auto* json = m_refIResources.GetJson(jsonName);
	if (!json)
	{
		return;
	}

	// 要素ごとにループ
	for (const auto& element : *json)
	{
		std::unique_ptr<GameObject> gameObject = Create(element);
		m_pGameObjects->push_back(std::move(gameObject));
	}
}

// ゲームオブジェクトを名前で検索
GameObject* GameObjects::GameObjectManager::Find(const std::string& name) const
{
	auto it = std::ranges::find_if(*m_pGameObjects, [&](const std::unique_ptr<GameObject>& gameObject) {return gameObject->GetName() == name; });
	if (it == m_pGameObjects->end())
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
		return it->get();
	}
}

// ゲームオブジェクトを生成
GameObject* GameObjects::GameObjectManager::Instantiate(const std::string& jsonName, bool dontDestroyOnLoad)
{
	// Json
	const auto* json = m_refIResources.GetJson(jsonName);
	if (!json)
	{
		return m_nullReference.get();
	}

	// ゲームオブジェクト
	std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>(m_pIComponentManager);
	// ポインタ
	GameObject* pGameObject = gameObject.get();
	pGameObject->SetName(jsonName);
	SetComponents(*json, pGameObject);

	if (dontDestroyOnLoad)
	{
		m_dontDestroyOnLoadGameObjects.push_back(std::move(gameObject));
	}
	else
	{
		m_pGameObjects->push_back(std::move(gameObject));
	}

	return pGameObject;
}

// ゲームオブジェクトを作成
std::unique_ptr<GameObject> GameObjects::GameObjectManager::Create(const nlohmann::ordered_json& json)
{
	std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>(m_pIComponentManager);
	for (const auto& element : json.items())
	{
		// 名前
		if (element.key() == "Name" && element.value().is_string())
		{
			gameObject->SetName(element.value().get<std::string>());
		}
		// Prefab
		else if (element.key() == "Prefab" && element.value().is_string())
		{
			// Json
			const auto* json = m_refIResources.GetJson(element.value().get<std::string>());
			if (!json)
			{
				continue;
			}

			SetComponents(*json, gameObject.get());
		}
		// コンポーネント
		else if (element.key() == "Components")
		{
			SetComponents(element.value(), gameObject.get());
		}
	}
	return gameObject;
}

// コンポーネントを設定
void GameObjects::GameObjectManager::SetComponents(const nlohmann::ordered_json& json, GameObject* pGameObject)
{
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
		auto* component = it->second(pGameObject);

		// コンポーネントの初期化
		component->Initalize(element.value(), this);
	}
}
