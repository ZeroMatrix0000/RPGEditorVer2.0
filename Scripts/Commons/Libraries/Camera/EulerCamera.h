/*
 * FileName:     EulerCamera.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * カメラ（オイラー）
 */

#pragma once

namespace Libraries
{
	namespace Camera
	{
		struct EulerCamera
		{

			/* メンバ関数 */

			// コンストラクタ
			constexpr EulerCamera()
				: position{ Math::Vector3::Zero }
				, rotation{}
			{
			}
			// コンストラクタ
			constexpr EulerCamera(const Math::Vector3& position, const Math::Euler& rotation)
				: position{ position }
				, rotation{ rotation }
			{
			}

			// ビュー行列を作成
			Math::Matrix CreateViewMatrix() const;


			/* 静的関数 */

			// 線形補間
			static EulerCamera Lerp(const EulerCamera& x, const EulerCamera& y, float t)
			{
				return EulerCamera{ Math::Vector3::Lerp(x.position, y.position, t), Math::Euler::Lerp(x.rotation, y.rotation, t) };
			}


			/* メンバ変数 */

			// 位置
			Math::Vector3 position;
			// 回転
			Math::Euler   rotation;

		};
	}
}
