/*
 * FileName:     ITimer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * タイマーのインタフェース
 */

#pragma once

#include "OnlyOne.h"

namespace Systems
{
	// タイマーのインタフェース
	class ITimer : public OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ITimer()
			: OnlyOne{ typeid(ITimer) }
		{
		}
		// デストラクタ
		virtual ~ITimer() = default;

		// 1F間の経過時間を取得
		virtual float GetDeltaTime() const = 0;

	};
}
