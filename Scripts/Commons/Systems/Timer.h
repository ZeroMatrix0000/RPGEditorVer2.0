/*
 * FileName:     Timer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * タイマー
 */

#pragma once

#include "ITimer.h"

namespace Systems
{
	// タイマー
	class Timer : public ITimer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Timer();

		// 初期化処理
		void Initialize();
		// 更新処理
		void Update();

		// 1F間の経過時間を取得
		float GetDeltaTime() const override { return (m_time.QuadPart - m_oldTime.QuadPart) / 1e7f; }


	private:


		/* メンバ変数 */

		// 経過時間[1e-7s]
		LARGE_INTEGER m_time;
		// 1F前の経過時間[1e-7s]
		LARGE_INTEGER m_oldTime;

	};
}