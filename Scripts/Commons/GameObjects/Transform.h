/*
 * FileName:     Transform.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * トランスフォーム
 */

#pragma once

#include "Component.h"

namespace GameObjects
{
	// トランスフォーム
	class Transform : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Transform(const ComponentCreatePermit& permit, GameObject* pOwner);

		// 座標を設定
		void SetPosition(const Math::Vector3& position)    { m_position = position; }
		// 回転を設定
		void SetRotation(const Math::Quaternion& rotation) { m_rotation = rotation; }
		// 拡大を設定
		void SetScale(const Math::Vector3& scale)          { m_scale = scale; }

		// ワールド行列を作成
		Math::Matrix CreateWorldMatrix() const;


	private:


		/* メンバ変数 */

		// 座標
		Math::Vector3 m_position;
		// 回転
		Math::Quaternion m_rotation;
		// 拡大
		Math::Vector3 m_scale;

	};
}
