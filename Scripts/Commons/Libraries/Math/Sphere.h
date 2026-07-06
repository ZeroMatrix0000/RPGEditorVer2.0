/*
 * FileName:     Sphere.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 球
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
		// 球
		struct Sphere
		{

			/* メンバ関数 */

			// コンストラクタ
			constexpr Sphere()
				: centerPosition{ Vector3::Zero }
				, radius{ 0.0f }
			{
			}

			// コンストラクタ
			constexpr Sphere(const Vector3& centerPosition, float radius)
				: centerPosition{ centerPosition }
				, radius{ radius }
			{
			}


			/* メンバ変数 */

			// 中心座標
			Vector3 centerPosition;
			// 半径
			float   radius;

		};
	}
}
