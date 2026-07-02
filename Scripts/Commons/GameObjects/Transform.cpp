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
	, position{ Math::Vector3::Zero }
	, rotation{ Math::Quaternion::Identity }
	, scale{ Math::Vector3::One }
{
}
