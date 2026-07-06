/*
 * FileName:     NonRotatingBox.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 非回転直方体
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
		// 非回転直方体
		struct NonRotatingBox
		{

			/* メンバ関数 */

			// コンストラクタ
			constexpr NonRotatingBox()
				: position{ Vector3::Zero }
				, size{ Vector3::One }
			{
			}
			// コンストラクタ
			constexpr NonRotatingBox(const Vector3& position, const Vector3& size)
				: position{ position }
				, size{ size }
			{
			}


			/* メンバ変数 */

			// 中心座標
			Vector3 position;
			// 大きさ
			Vector3 size;

		};
	}
}
