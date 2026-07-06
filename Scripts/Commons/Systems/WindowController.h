/*
 * FileName:     WindowController.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * ウィンドウ管理
 */

#pragma once

#include "IWindowController.h"

namespace Systems
{
	// ウィンドウ管理
	class WindowController : public IWindowController
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		WindowController();

		// 初期化処理
		void Initialize(const HWND& hWindow);

		// フルスクリーン表示切り替え
		void ChangeFullScreen() override;
		// ウィンドウを破棄
		void Destroy() const override;

		// 出力サイズを取得
		const Math::Vector2& GetOutputSize() const override { return m_outputSize; }

		// 出力サイズを設定
		void SetOutputSize(const Math::Vector2& outputSize) { m_outputSize = outputSize; }


	private:


		/* メンバ変数 */

		// ウィンドウへのハンドル
		HWND m_hWindow;

		// フルスクリーンかどうか
		bool m_isFullScreen;
		// ウィンドウ長方形
		RECT m_rect;

		// 出力サイズ
		Math::Vector2 m_outputSize;

	};
}
