/*
 * FileName:     Line.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * 線分
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
		struct Line
		{

			/* メンバ関数 */

			// コンストラクタ
			constexpr Line()
				: v1{ Vector3::Zero }
				, v2{ Vector3::Zero }
			{
			}

			// コンストラクタ
			constexpr Line(const Vector3& v1, const Vector3& v2)
				: v1{ v1 }
				, v2{ v2 }
			{
			}


			/* メンバ変数 */

			// 端点1
			Vector3 v1;
			// 端点2
			Vector3 v2;

		};
	}
}
