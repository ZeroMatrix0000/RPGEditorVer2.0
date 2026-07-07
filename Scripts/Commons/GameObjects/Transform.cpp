/*
 * FileName:     Transform.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/02
 *
 * トランスフォーム
 */

#include "Pch.h"
#include "Transform.h"

GameObjects::Transform::Transform(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Component{ permit, pOwner }
	, m_position{ Math::Vector3::Zero }
	, m_rotation{ Math::Quaternion::Identity }
	, m_scale{ Math::Vector3::One }
{
}

// ワールド行列を作成
Math::Matrix GameObjects::Transform::CreateWorldMatrix() const
{
	return Math::Matrix::CreateScale(m_scale) * Math::Matrix::CreateFromQuaternion(m_rotation) * Math::Matrix::CreateTranslation(m_position);
}
