/*
 * FileName:     RectTransform.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 2D用トランスフォーム
 */

#pragma once

#include "Component.h"

namespace GameObjects
{
	// 2D用トランスフォーム
	class RectTransform : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		RectTransform(const ComponentCreatePermit& permit, GameObject* pOwner);

		// 座標を設定
		void SetPosition(const Math::Vector2& position) { m_rect.position = position; }
		// 大きさを設定
		void SetSize(const Math::Vector2& size) { m_rect.size = size; }


	private:


		// 長方形
		Math::Rect m_rect;
		// 角度
		float m_angle;

		// ピボット
		Utility::AlignmentPoint m_pivot;
		// アンカー
		Utility::AlignmentPoint m_anchor;

	};
}