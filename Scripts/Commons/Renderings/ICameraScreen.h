/*
 * FileName:     ICameraScreen.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * カメラ画面のインタフェース
 */

#pragma once

#include "../GameObjects/Component.h"

namespace Renderings
{
	class ICameraScreen : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ICameraScreen(const ComponentCreatePermit& permit, GameObject* pOwner)
			: Component{ permit, pOwner }
		{
		}

		// ビュー行列を取得
		virtual const Math::Matrix& GetViewMatrix() const = 0;
		// プロジェクション行列を取得
		virtual const Math::Matrix& GetProjectionMatrix() const = 0;

	};
}
