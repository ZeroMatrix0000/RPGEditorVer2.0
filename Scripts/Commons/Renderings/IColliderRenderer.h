/*
 * FileName:     IColliderRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * 当たり判定描画のインタフェース
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace Colliders
{
	class BoxCollider;
}

namespace Renderings
{
	class IColliderRenderer : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		IColliderRenderer()
			: OnlyOne{ typeid(IColliderRenderer) }
		{
		}
		// デストラクタ
		virtual ~IColliderRenderer() = default;

		// 長方形当たり判定のポインタを追加
		virtual void AddPBoxCollider(const Colliders::BoxCollider* pBoxCollider) = 0;
		// 長方形当たり判定のポインタを削除
		virtual void RemovePBoxCollider(const Colliders::BoxCollider* pBoxCollider) = 0;

	};
}
