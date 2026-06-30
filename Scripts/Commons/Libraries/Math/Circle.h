/*
 * FileName:     Circle.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * 円
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
		struct Circle
		{

			/* メンバ関数 */

			// コンストラクタ
			constexpr Circle()
				: centerPosition{ Vector3::Zero }
				, radius{ 0.0f }
				, axis{ Vector3::Zero }
			{
			}

			// コンストラクタ
			constexpr Circle(const Vector3& centerPosition, float radius, const Vector3& axis)
				: centerPosition{ centerPosition }
				, radius{ radius }
				, axis{ axis }
			{
			}


			/* メンバ変数 */

			// 中心座標
			Vector3 centerPosition;
			// 半径
			float   radius;
			// 軸
			Vector3 axis;

		};
	}
}
