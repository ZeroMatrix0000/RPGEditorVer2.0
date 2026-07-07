/*
 * FileName:     ComponentManager.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
 *
 * コンポーネント管理
 */

#include "Pch.h"
#include "ComponentManager.h"

// コンストラクタ
GameObjects::ComponentManager::ComponentManager()
	: IComponentManager{}
	, m_permit{}
{
}

// コンポーネントを作成
std::unique_ptr<Component> GameObjects::ComponentManager::Create(const std::type_index& index, GameObject* pOwner) const
{
	return m_CreateComponentList.at(index)(m_permit, pOwner);
}
