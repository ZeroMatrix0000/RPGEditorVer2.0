/*
 * FileName:     GameObjectManager.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/15
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
void GameObjects::GameObjectManager::Load(const std::string& jsonName) const
{
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
			Instantiate(element.value().get<std::string>());
		}
		else
		{
			std::unique_ptr<GameObject> gameObject = Create(element.value());
			gameObject->SetName(element.key());
			if (gameObject)
			{
				m_pGameObjects->push_back(std::move(gameObject));
			}
		}
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
GameObject* GameObjects::GameObjectManager::Instantiate(const std::string& jsonName) const
{
	// Json
	const auto* json = m_refIResources.GetJson(jsonName);
	if (!json)
	{
		return m_nullReference.get();
	}

	// ゲームオブジェクト
	std::unique_ptr<GameObject> gameObject = Create(*json);
	// ポインタ
	GameObject* pGameObject = gameObject.get();
	pGameObject->SetName(jsonName);
	m_pGameObjects->push_back(std::move(gameObject));
	return pGameObject;
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

		try
		{
			// コンポーネントの初期化
			component->Initalize(element.value());
		}
		catch (std::exception e)
		{
			// エラーメッセージを追加
			Systems::IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
			(
				L"コンポーネントの初期化に失敗しました。 | name: %s",
				Utility::string2wstring(element.key()).c_str()
			));
			continue;
		}
	}
	return gameObject;
}
