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
	class SphereCollider;
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

		// 長方形の当たり判定のポインタを追加
		virtual void AddPBoxCollider(const Colliders::BoxCollider* pBoxCollider) = 0;
		// 長方形の当たり判定のポインタを削除
		virtual void RemovePBoxCollider(const Colliders::BoxCollider* pBoxCollider) = 0;

		// 球の当たり判定のポインタを追加
		virtual void AddPSphereCollider(const Colliders::SphereCollider* pSphereCollider) = 0;
		// 球の当たり判定のポインタを削除
		virtual void RemovePSphereCollider(const Colliders::SphereCollider* pSphereCollider) = 0;

	};
}
