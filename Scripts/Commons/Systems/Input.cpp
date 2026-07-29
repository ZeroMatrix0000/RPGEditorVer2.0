/*
 * FileName:     Input.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/29
 *
 * 入力管理
 */

#include "Pch.h"
#include "Input.h"

 // コンストラクタ
Systems::Input::Input()
	: IInput{}
	, m_keyboard{}
	, m_keyboardState{}
	, m_keyboardStateOld{}
	, m_mouse{}
	, m_mouseState{}
	, m_mouseStateOld{}
	, m_mousePositionLoop{}
{
}

// 初期化処理
void Systems::Input::Initialize()
{
	m_keyboardState = m_keyboard.GetState();
	m_mouseState    = m_mouse.GetState();
	MousePositionCorrect();
}

// 更新処理
void Systems::Input::Update()
{
	m_keyboardStateOld = m_keyboardState;
	m_keyboardState    = m_keyboard.GetState();
	m_mouseStateOld    = m_mouseState;
	m_mouseState       = m_mouse.GetState();
	MousePositionCorrect();
}

bool Systems::Input::GetMouseButton(MouseButtonName mouseButtonName) const
{
	switch (mouseButtonName)
	{
	case MouseButtonName::Left:
		return m_mouseState.leftButton;
	case MouseButtonName::Middle:
		return m_mouseState.middleButton;
	case MouseButtonName::Right:
		return m_mouseState.rightButton;
	default:
		return false;
	}
}

// マウスのボタンの離状態を取得
bool Systems::Input::GetMouseButtonUp(MouseButtonName mouseButtonName) const
{
	switch (mouseButtonName)
	{
	case MouseButtonName::Left:
		return !m_mouseState.leftButton   && m_mouseStateOld.leftButton;
	case MouseButtonName::Middle:
		return !m_mouseState.middleButton && m_mouseStateOld.middleButton;
	case MouseButtonName::Right:
		return !m_mouseState.rightButton  && m_mouseStateOld.rightButton;
	default:
		return false;
	}
}

// マウスカーソルを表示
void Systems::Input::DisplayCursor(bool isShow)
{
	ShowCursor(isShow);
}

// マウスの座標の計算
void Systems::Input::MousePositionCorrect()
{
	// マウスの位置
	POINT mousePosition{};
	GetCursorPos(&mousePosition);

	// マウス座標をループさせるなら
	if (m_mousePositionLoop)
	{
		// スクリーン幅
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		// スクリーン高さ
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		// 座標を変更したか
		bool isChanged = false;
		// 画面端にカーソルがある場合反対側に移動
		if (mousePosition.x == 0)
		{
			isChanged = true;
			mousePosition.x = screenWidth - 2;
		}
		if (mousePosition.x == screenWidth - 1)
		{
			isChanged = true;
			mousePosition.x = 1;
		}
		if (mousePosition.y == 0)
		{
			isChanged = true;
			mousePosition.y = screenHeight - 2;
		}
		if (mousePosition.y == screenHeight - 1)
		{
			isChanged = true;
			mousePosition.y = 1;
		}

		if (isChanged)
		{
			// 変更前の座標
			POINT oldMousePosition{};
			GetCursorPos(&oldMousePosition);

			SetCursorPos(mousePosition.x, mousePosition.y);

			m_mouseStateOld.x += mousePosition.x - oldMousePosition.x;
			m_mouseStateOld.y += mousePosition.y - oldMousePosition.y;
		}
	}

	m_mouseState.x = mousePosition.x;
	m_mouseState.y = mousePosition.y;
}

// マウスのボタンの押状態を取得
bool Systems::Input::GetMouseButtonDown(MouseButtonName mouseButtonName) const
{
	switch (mouseButtonName)
	{
	case MouseButtonName::Left:
		return m_mouseState.leftButton   && !m_mouseStateOld.leftButton;
	case MouseButtonName::Middle:
		return m_mouseState.middleButton && !m_mouseStateOld.middleButton;
	case MouseButtonName::Right:
		return m_mouseState.rightButton  && !m_mouseStateOld.rightButton;
	default:
		return false;
	}
}
