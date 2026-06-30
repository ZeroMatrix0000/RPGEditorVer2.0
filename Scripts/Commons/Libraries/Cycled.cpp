/*
 * FileName:     Cycled.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * ループ値
 */

#include "Pch.h"

// コンストラクタ
Libraries::Cycled::Cycled()
	: m_value{}
	, m_min{}
	, m_max{}
{
}

// 初期化処理
void Libraries::Cycled::Initialize(float value, float min, float max)
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

	m_value = Math::Cycle(value, m_min, m_max);
}

Cycled& Libraries::Cycled::operator+=(float value)
{
	m_value = Math::Cycle(m_value + value, m_min, m_max);
	return *this;
}

Cycled& Libraries::Cycled::operator-=(float value)
{
	m_value = Math::Cycle(m_value - value, m_min, m_max);
	return *this;
}

Cycled& Libraries::Cycled::operator=(float value)
{
	m_value = Math::Cycle(value, m_min, m_max);
	return *this;
}

// 生成
Cycled Libraries::Cycled::Create(float value, float min, float max)
{
	Cycled cycled;
	cycled.Initialize(value, min, max);
	return cycled;
}
