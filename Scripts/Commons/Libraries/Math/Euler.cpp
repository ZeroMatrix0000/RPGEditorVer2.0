/*
 * FileName:     Euler.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * オイラー角
 */

#include "Pch.h"

 // フォーマットを整える
Math::Euler& Libraries::Math::Euler::Format()
{
	x = Math::Cycle(x, -180.0f, 180.0f);
	y = Math::Cycle(y, -180.0f, 180.0f);
	z = Math::Cycle(z, -180.0f, 180.0f);
	return *this;
}

// 線形補間
Math::Euler Libraries::Math::Euler::Lerp(const Euler& x, const Euler& y, float t)
{
	Euler delta = (y - x).Format();
	Euler v = Vector3::Lerp(x, x + delta, t);
	return v.Format();
}
