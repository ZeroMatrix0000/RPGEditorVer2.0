/*
 * FileName:     Sphere.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * 球
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
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
