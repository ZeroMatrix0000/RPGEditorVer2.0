/*
 * FileName:     WindowController.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * ウィンドウ管理
 */

#include "Pch.h"
#include "WindowController.h"

// コンストラクタ
Systems::WindowController::WindowController()
	: IWindowController{}
	, m_hWindow{}
	, m_isFullScreen{}
	, m_rect{}
	, m_outputSize{}
{
}

// 初期化処理
void Systems::WindowController::Initialize(const HWND& hWindow)
{
	m_hWindow = hWindow;

	// クライアントサイズ
	RECT clientRect{};
	GetClientRect(hWindow, &clientRect);

	// 出力サイズを設定
	m_outputSize.x = static_cast<float>(clientRect.right - clientRect.left);
	m_outputSize.y = static_cast<float>(clientRect.bottom - clientRect.top);
}

// フルスクリーン表示切り替え
void Systems::WindowController::ChangeFullScreen()
{
	m_isFullScreen = !m_isFullScreen;

	// フルスクリーン
	if (m_isFullScreen)
	{
		// ウィンドウの枠を無くす
		SetWindowLongPtrW(m_hWindow, GWL_STYLE, WS_POPUP);

		// ウィンドウ長方形を取得
		GetWindowRect(m_hWindow, &m_rect);

		// 最大表示
		ShowWindow(m_hWindow, SW_SHOWMAXIMIZED);
	}
	else
	{
		// ウィンドウを元のスタイルに戻す
		SetWindowLongPtrW(m_hWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		// ウィンドウモードに戻す
		ShowWindow(m_hWindow, SW_RESTORE);

		// ワークエリアサイズ
		RECT workArea{};
		SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);

		Math::Vector2Int position =
		{
			(workArea.right - workArea.left - m_rect.right + m_rect.left) / 2,
			workArea.bottom - workArea.top < m_rect.bottom - m_rect.top ? 0 : (workArea.bottom - workArea.top - m_rect.bottom + m_rect.top) / 2
		};

		// ウィンドウ配置
		SetWindowPos
		(
			m_hWindow,
			nullptr,
			position.x,
			position.y,
			m_rect.right - m_rect.left,
			m_rect.bottom - m_rect.top,
			SWP_NOZORDER
		);
	}
}

// ウィンドウを破棄
void Systems::WindowController::Destroy() const
{
	// ウィンドウを破棄
	DestroyWindow(m_hWindow);
}
