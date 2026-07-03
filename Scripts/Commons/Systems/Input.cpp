/*
 * FileName:     Input.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
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
{
}

// 初期化処理
void Systems::Input::Initialize()
{
	m_keyboardState = m_keyboard.GetState();
	m_mouseState    = m_mouse.GetState();
}

// 更新処理
void Systems::Input::Update()
{
	m_keyboardStateOld = m_keyboardState;
	m_keyboardState    = m_keyboard.GetState();
	m_mouseStateOld    = m_mouseState;
	m_mouseState       = m_mouse.GetState();
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
