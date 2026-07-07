/*
 * FileName:     Canvas.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
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
	, m_ratio{}
{
}

// 初期化処理
void Renderings::Canvas::Initialize(FixedSize fixedSize, const Math::Vector2& outputSize)
{
	m_fixedSize = fixedSize;
	SetSize(outputSize);
}

// サイズを設定
void Renderings::Canvas::SetSize(const Math::Vector2& outputSize)
{
	switch (m_fixedSize)
	{
	case Renderings::Canvas::FixedSize::None:
		m_ratio = 1.0f;
		break;
	case Renderings::Canvas::FixedSize::Horizontal:
		m_ratio = outputSize.x / DEFAULT_SIZE.x;
		break;
	case Renderings::Canvas::FixedSize::Vertical:
		m_ratio = outputSize.y / DEFAULT_SIZE.y;
		break;
	default:
		break;
	}

	m_size = outputSize / m_ratio;
}
