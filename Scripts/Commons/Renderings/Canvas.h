/*
 * FileName:     Canvas.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * カメラ画面
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace Renderings
{
	class Canvas : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Canvas();


	private:


		/* 定数 */

		// キャンバスのデフォルトサイズ
		static constexpr Math::Vector2 DEFAULT_SIZE = Math::Vector2{ 1600.0f, 900.0f };

	};
}
