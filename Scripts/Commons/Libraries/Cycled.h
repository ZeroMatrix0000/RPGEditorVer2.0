/*
 * FileName:     Cycled.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
 *
 * ループ値
 */

#pragma once

namespace Libraries
{
	// ループ値
	class Cycled
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Cycled();

		// 初期化処理
		void Initialize(float value, float min, float max);

		// 最小値かどうかを取得
		bool IsMin() const { return m_value == m_min; }
		// 最大値かどうかを取得
		bool IsMax() const { return m_value == m_max; }

		// 最小値を取得
		float GetMin() const { return m_min; }
		// 最大値を取得
		float GetMax() const { return m_max; }

		// 割合を取得
		float GetRatio() const { return m_max - m_min == 0.0f ? 1.0f : (m_value - m_min) / (m_max - m_min); }


		/* 演算子オーバーロード */

		Cycled& operator+=(float value);
		Cycled& operator-=(float value);
		Cycled& operator= (float value);

		operator float() const { return m_value; }


		/* 静的関数 */

		// 生成
		static Cycled Create(float value, float min, float max);


	private:


		/* メンバ変数 */

		// 値
		float m_value;
		// 最小値
		float m_min;
		// 最大値
		float m_max;

	};
}
