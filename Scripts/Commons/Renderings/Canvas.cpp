/*
 * FileName:     Canvas.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * カメラ画面
 */

#include "Pch.h"
#include "Canvas.h"

// コンストラクタ
Renderings::Canvas::Canvas(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Component{ permit, pOwner }
	, m_fixedSize{}
	, m_size{}
{
}

// サイズを設定
void Renderings::Canvas::SetSize(const Math::Vector2& outputSize)
{
	switch (m_fixedSize)
	{
	case Renderings::Canvas::FixedSize::None:
		m_size = outputSize;
		break;
	case Renderings::Canvas::FixedSize::Horizontal:
		m_size = outputSize * DEFAULT_SIZE.x / outputSize.x;
		break;
	case Renderings::Canvas::FixedSize::Vertical:
		m_size = outputSize * DEFAULT_SIZE.y / outputSize.y;
		break;
	default:
		break;
	}
}
