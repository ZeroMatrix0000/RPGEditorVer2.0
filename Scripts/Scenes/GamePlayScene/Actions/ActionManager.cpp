/*
 * FileName:     ActionManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/08
 *
 * アクション管理
 */

#include "Pch.h"
#include "ActionManager.h"

#include "Scripts/Commons/Systems/IResources.h"

// コンストラクタ
ActionManager::ActionManager(const ComponentDesc& desc, const Systems::IResources& iResources)
	: Component{ desc }
	, m_eventCount{}
	, m_eventIndex{}
	, m_pEvent{}
	, m_refIResources{ iResources }
{
}

// 初期化処理
void ActionManager::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
}

// イベントを設定
void ActionManager::LoadEvent(const std::string& eventName)
{
	m_pEvent = m_refIResources.GetJson(eventName);

	m_eventCount = m_pEvent->size();
	m_eventIndex = 0;
}
