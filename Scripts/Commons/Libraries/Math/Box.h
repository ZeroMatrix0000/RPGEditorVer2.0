/*
 * FileName:     Box.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/31
 *
 * 直方体
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
		struct Box
		{

			/* メンバ関数 */

			// コンストラクタ
			constexpr Box()
				: position{ Vector3::Zero }
				, size{ Vector3::One }
				, rotation{ Quaternion::Identity }
			{
			}
			// コンストラクタ
			constexpr Box(const Vector3& position, const Vector3& size, const Quaternion& rotation)
				: position{ position }
				, size{ size }
				, rotation{ rotation }
			{
			}
			// コンストラクタ
			constexpr Box(const NonRotatingBox& box)
				: position{ box.position }
				, size{ box.size }
				, rotation{ Quaternion::Identity }
			{
			}

			// 外接する非回転直方体を生成
			NonRotatingBox CreateNonRotatingBox() const;

			// 頂点を取得
			Vector3 GetVertex(bool isPositiveX, bool isPositiveY, bool isPositiveZ) const;
			// 頂点の配列を取得
			std::array<Vector3, 8> GetVertices() const;


			/* メンバ変数 */

			// 中心座標
			Vector3 position;
			// 大きさ
			Vector3 size;
			// 回転
			Quaternion rotation;

		};
	}
}
