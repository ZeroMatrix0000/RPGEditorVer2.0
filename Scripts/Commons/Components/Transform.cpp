/*
 * FileName:     Transform.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
 *
 * トランスフォーム
 */

#include "Pch.h"
#include "Transform.h"

#include "../Systems/JsonSerializer.h"

Components::Transform::Transform(const ComponentDesc& desc)
	: Component{ desc }
	, m_position{ Math::Vector3::Zero }
	, m_rotation{ Math::Quaternion::Identity }
	, m_scale{ Math::Vector3::One }
{
}

// 初期化処理
void Components::Transform::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_position, "Position");
	serializer.AddParameter(&m_rotation, "Rotation");
	serializer.AddParameter(&m_scale, "Scale");
	serializer.Load(json);
}

// ワールド行列を作成
Math::Matrix Components::Transform::CreateWorldMatrix() const
{
	return Math::Matrix::CreateScale(m_scale) * Math::Matrix::CreateFromQuaternion(m_rotation) * Math::Matrix::CreateTranslation(m_position);
}
