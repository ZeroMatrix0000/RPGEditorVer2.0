/*
 * FileName:     Canvas.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
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

		// キャンバスサイズの設定方法を設定
		void SetFixedState(FixedSize fixedState) { m_fixedSize = fixedState; }
		
		// サイズを設定
		void SetSize(const Math::Vector2& outputSize);


	private:


		/* 定数 */

		// キャンバスのデフォルトサイズ
		static constexpr Math::Vector2 DEFAULT_SIZE = Math::Vector2{ 1600.0f, 900.0f };


		/* メンバ変数 */

		// キャンバスサイズの設定方法
		FixedSize m_fixedSize;

		// キャンバスサイズ
		Math::Vector2 m_size;

	};
}
