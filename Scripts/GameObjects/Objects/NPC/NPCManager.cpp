/*
 * FileName:     NPCManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/22
 *
 * NPC管理
 */

#include "Pch.h"
#include "NPCManager.h"

#include "Scripts/Commons/Systems/JsonSerializer.h"

// コンストラクタ
NPCManager::NPCManager(const ComponentDesc& desc)
	: Component{ desc }
	, m_pNPCList{}
{
}

// 初期化処理
void NPCManager::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_pNPCList, "NPCList");
	serializer.Load(json);
}

// 更新処理
void NPCManager::Update(float elapsedTime)
{
}
