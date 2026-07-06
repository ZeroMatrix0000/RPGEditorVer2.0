/*
 * FileName:     Rect.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 長方形
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
		// 長方形
		struct Rect
		{

			/* メンバ関数 */

			// コンストラクタ
			Rect()
				: position{}
				, size{}
			{
			}
			// コンストラクタ
			Rect(const Vector2& position, const Vector2& size)
				: position{ position }
				, size{ size }
			{
			}

			// D2D1_RECT_F型に変換
			D2D1_RECT_F CreateD2D1_RECT_F() const
			{
				return D2D1_RECT_F
				{
					position.x - size.x / 2.0f,
					position.y - size.y / 2.0f,
					position.x + size.x / 2.0f,
					position.y + size.y / 2.0f
				};
			}


			/* メンバ変数 */

			// 中心座標
			Vector2 position;
			// 大きさ
			Vector2 size;

		};
	}
}
