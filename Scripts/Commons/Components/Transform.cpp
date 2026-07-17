/*
 * FileName:     Transform.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/17
 *
 * トランスフォーム
 */

#include "Pch.h"
#include "Transform.h"

Components::Transform::Transform(const ComponentDesc& desc)
	: Component{ desc }
	, m_position{ Math::Vector3::Zero }
	, m_rotation{ Math::Quaternion::Identity }
	, m_scale{ Math::Vector3::One }
{
}

// ワールド行列を作成
Math::Matrix Components::Transform::CreateWorldMatrix() const
{
	return Math::Matrix::CreateScale(m_scale) * Math::Matrix::CreateFromQuaternion(m_rotation) * Math::Matrix::CreateTranslation(m_position);
}
