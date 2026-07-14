/*
 * FileName:     ComponentManager.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * コンポーネント管理
 */

#include "Pch.h"
#include "ComponentManager.h"

#include "../Systems/IErrorMessage.h"

// コンストラクタ
GameObjects::ComponentManager::ComponentManager()
	: IComponentManager{}
	, m_permit{}
	, m_CreateComponentList{}
	, m_nullReferences{}
{
}

// コンポーネントを作成
std::unique_ptr<Component> GameObjects::ComponentManager::Create(const std::type_index& index, GameObject* pOwner)
{
	return m_CreateComponentList.at(index)(m_permit, pOwner);
}

// コンポーネント作成関数を追加
void GameObjects::ComponentManager::RegisterCreate
(
	const std::type_index& index,
	const std::function<std::unique_ptr<Component>(ComponentCreatePermit, GameObject*)>& CreateComponent
)
{
	m_CreateComponentList.emplace(index, CreateComponent);
}

// 未参照コンポーネントを取得
Component* GameObjects::ComponentManager::GetNullReferences(const std::type_index& index)
{
	// エラーメッセージを追加
	Systems::IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
	(
		L"コンポーネントが見つかりません。 | %s",
		Utility::string2wstring(index.name()).c_str()
	));
	auto it = m_nullReferences.find(index);
	if (it == m_nullReferences.end())
	{
		// コンポーネントを追加
		m_nullReferences.emplace(index, (m_CreateComponentList.at(index)(m_permit, nullptr)));
		return m_nullReferences.at(index).get();
	}
	else
	{
		return it->second.get();
	}
}
