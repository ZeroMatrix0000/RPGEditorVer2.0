/*
 * FileName:     RectTransform.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 2D用トランスフォーム
 */

#include "Pch.h"
#include "RectTransform.h"

// コンストラクタ
GameObjects::RectTransform::RectTransform(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Component{ permit, pOwner }
	, m_rect{}
	, m_angle{}
	, m_pivot{}
	, m_anchor{}
{
}
