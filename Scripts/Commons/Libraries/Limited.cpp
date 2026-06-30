/*
 * FileName:     Limited.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * 範囲値
 */

#include "Pch.h"

// コンストラクタ
Libraries::Limited::Limited()
	: m_value{}
	, m_min{}
	, m_max{}
{
}

// 初期化処理
void Libraries::Limited::Initialize(float value, float min, float max)
{
	if (min < max)
	{
		m_min = min;
		m_max = max;
	}
	else
	{
		m_min = max;
		m_max = min;
	}

	m_value = Math::Clamp(value, m_min, m_max);
}

Limited& Libraries::Limited::operator+=(float value)
{
	m_value = Math::Clamp(m_value + value, m_min, m_max);
	return *this;
}

Limited& Libraries::Limited::operator-=(float value)
{
	m_value = Math::Clamp(m_value - value, m_min, m_max);
	return *this;
}

Limited& Libraries::Limited::operator=(float value)
{
	m_value = Math::Clamp(value, m_min, m_max);
	return *this;
}

// 生成
Limited Libraries::Limited::Create(float value, float min, float max)
{
	Limited limited;
	limited.Initialize(value, min, max);
	return limited;
}
