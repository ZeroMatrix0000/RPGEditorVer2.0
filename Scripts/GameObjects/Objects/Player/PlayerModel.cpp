/*
 * FileName:     PlayerModel.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/10
 *
 * プレイヤーのモデル
 */

#include "Pch.h"
#include "PlayerModel.h"

#include "Scripts/Commons/Components/Transform.h"
#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Systems/JsonSerializer.h"

// コンストラクタ
PlayerModel::PlayerModel(const ComponentDesc& desc)
	: Component{ desc }
	, m_pTransform{ GetPOwner()->GetNullReferences<Transform>() }
{
}

// 初期化処理
void PlayerModel::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	m_pTransform = GetPOwner()->GetComponent<Transform>();
}

// 更新処理
void PlayerModel::Update(float elapsedTime)
{
}

// トランスフォームを設定
void PlayerModel::SetTransform(const Transform& transform)
{
	m_pTransform->SetPosition(transform.GetPosition());
	m_pTransform->SetRotation(transform.GetRotation());
	m_pTransform->SetScale(transform.GetScale());
}
