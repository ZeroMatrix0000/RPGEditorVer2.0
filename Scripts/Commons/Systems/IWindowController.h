/*
 * FileName:     IWindowController.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * ウィンドウ管理のインタフェース
 */

#pragma once

#include "OnlyOne.h"

namespace Systems
{
	class IWindowController : public OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		IWindowController()
			: OnlyOne{ typeid(IWindowController) }
		{
		}
		// デストラクタ
		virtual ~IWindowController() = default;

		// フルスクリーン表示切り替え
		virtual void ChangeFullScreen() = 0;
		// ウィンドウを破棄
		virtual void Destroy() const = 0;

		// 出力サイズを取得
		virtual const Math::Vector2& GetOutputSize() const = 0;

	};
}
