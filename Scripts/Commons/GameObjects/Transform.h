/*
 * FileName:     Transform.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * トランスフォーム
 */

#pragma once

#include "Component.h"

namespace GameObjects
{
	class Transform : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Transform(const ComponentCreatePermit& permit);


	private:


		/* メンバ変数 */

		// 座標
		Math::Vector3 position;
		// 回転
		Math::Quaternion rotation;
		// 拡大率
		Math::Vector3 scale;

	};
}
