/*
 * FileName:     Transform.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/02
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
		Transform(const ComponentCreatePermit& permit, GameObject* pOwner);

		// 座標を設定
		void SetPosition(const Math::Vector3& position) { m_position = position; }

		// 座標を取得
		const Math::Vector3& GetPosition() const { return m_position; }


	private:


		/* メンバ変数 */

		// 座標
		Math::Vector3 m_position;
		// 回転
		Math::Quaternion m_rotation;
		// 拡大率
		Math::Vector3 m_scale;

	};
}
