/*
 * FileName:     Canvas.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
 *
 * カメラ画面
 */

#pragma once

#include "../GameObjects/Component.h"

namespace Renderings
{
	// カメラ画面
	class Canvas : public Component
	{

	public:


		/* 列挙型 */

		// キャンバスサイズの設定方法
		enum class FixedSize
		{
			None,
			Horizontal,
			Vertical
		};


		/* メンバ関数 */

		// コンストラクタ
		Canvas(const ComponentCreatePermit& permit, GameObject* pOwner);

		// 初期化処理
		void Initialize(FixedSize fixedSize, const Math::Vector2& outputSize);
		
		// サイズを設定
		void SetSize(const Math::Vector2& outputSize);

		// キャンバスの表示倍率を取得
		const Math::Vector2& GetSize() const { return m_size; }
		// キャンバスの表示倍率を取得
		float GetRatio() const { return m_ratio; }


	private:


		/* 定数 */

		// キャンバスのデフォルトサイズ
		static constexpr Math::Vector2 DEFAULT_SIZE = Math::Vector2{ 1600.0f, 900.0f };


		/* メンバ変数 */

		// キャンバスサイズの設定方法
		FixedSize m_fixedSize;

		// キャンバスサイズ
		Math::Vector2 m_size;
		// キャンバスの表示倍率
		float m_ratio;

	};
}
