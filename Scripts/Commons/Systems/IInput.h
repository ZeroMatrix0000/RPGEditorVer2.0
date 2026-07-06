/*
 * FileName:     IInput.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 入力管理のインタフェース
 */

#pragma once

#include "OnlyOne.h"

namespace Systems
{
	// 入力管理のインタフェース
	class IInput : public OnlyOne
	{

	public:


		/* 列挙型 */

		// キー名
		typedef DirectX::Keyboard::Keys KeyName;

		// マウスボタン名
		enum class MouseButtonName
		{
			Left,
			Middle,
			Right
		};


		/* メンバ関数 */

		// コンストラクタ
		IInput()
			: OnlyOne{ typeid(IInput) }
		{
		}
		// デストラクタ
		virtual ~IInput() = default;

		// キーの押状態を取得
		virtual bool GetKeyDown(KeyName keyName) const = 0;
		// キーの状態を取得
		virtual bool GetKey(KeyName keyName)     const = 0;
		// キーの離状態を取得
		virtual bool GetKeyUp(KeyName keyName)   const = 0;

		// Shiftキーの状態を取得
		virtual bool GetShiftKey()   const = 0;
		// Ctrlキーの状態を取得
		virtual bool GetCtrlKey()    const = 0;
		// Altキーの状態を取得
		virtual bool GetAltKey()     const = 0;

		// マウスのボタンの押状態を取得
		virtual bool GetMouseButtonDown(MouseButtonName mouseButtonName) const = 0;
		// マウスのボタンの状態を取得
		virtual bool GetMouseButton(MouseButtonName mouseButtonName)     const = 0;
		// マウスのボタンの離状態を取得
		virtual bool GetMouseButtonUp(MouseButtonName mouseButtonName)   const = 0;

		// マウスの位置を取得
		virtual Math::Vector2Int GetMousePosition()   const = 0;
		// マウスの移動量を取得
		virtual Math::Vector2Int GetMouseMovement()   const = 0;
		// マウスホイールの移動量を取得
		virtual int              GetMouseWheelDelta() const = 0;

	};
}

typedef Systems::IInput::KeyName         KeyName;
typedef Systems::IInput::MouseButtonName MouseButtonName;
