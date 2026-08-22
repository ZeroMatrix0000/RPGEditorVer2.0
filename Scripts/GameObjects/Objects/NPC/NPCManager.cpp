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
	, m_pFocusedNPC{}
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
	for (auto* pNPC : m_pNPCList)
	{
		pNPC->Update(elapsedTime);
	}
}

// 向きを設定
void NPCManager::SetRotation(const Math::Vector3& playerPosition)
{
	// 距離の最小
	float distanceMin = Math::INFTY;

	m_pFocusedNPC = nullptr;

	for (auto* pNPC : m_pNPCList)
	{
		// プレイヤーとの中心距離（XZ平面）
		float distance = ((playerPosition - pNPC->GetPosition()) * Math::Vector3{ 1.0f, 0.0f, 1.0f }).Length();
		// 距離がある程度近かったら
		if (distance < pNPC->GetFocusDistance())
		{
			// 向く方向
			Math::Vector3 direction = playerPosition - pNPC->GetPosition();
			// Y軸方向は無視
			direction.y = 0.0f;
			// 正規化
			direction.Normalize();
			// 回転
			Math::Quaternion rotation = Math::Quaternion::FromToRotation(Math::Vector3::Backward, direction);
			pNPC->SetRotation(&rotation);

			// 最も近いNPCを記録
			if (distance < distanceMin)
			{
				distanceMin = distance;
				m_pFocusedNPC = pNPC;
			}
		}
		else
		{
			pNPC->SetRotation();
		}
	}
}

// 当たり判定を取得
std::vector<const Math::Box*> NPCManager::GetPBoxes() const
{
	std::vector<const Math::Box*> pBoxes{};
	for (const auto* pNPC : m_pNPCList)
	{
		pBoxes.push_back(&pNPC->GetBox());
	}
	return pBoxes;
}
