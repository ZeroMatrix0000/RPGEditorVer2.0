/*
 * FileName:     OnlyOne.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 2つ以上実体を生成するとエラーを吐くクラス
 */

#pragma once

namespace Systems
{
	// 2つ以上実体を生成するとエラーを吐くクラス
	class OnlyOne
	{

	protected:


		/* メンバ関数 */

		// コンストラクタ
		OnlyOne(const std::type_index& index);
		// デストラクタ
		virtual ~OnlyOne();


	private:


		/* メンバ変数 */

		// クラス名
		std::type_index m_index;


		/* 静的変数 */

		// 型インデックスリスト
		static std::unordered_set<std::type_index> s_indices;

	};
}
