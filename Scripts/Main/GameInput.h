/*
 * FileName:     GameInput.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/31
 *
 * ゲームの入力
 */

#pragma once

#include "../Commons/Systems/IInput.h"
#include "IGameInput.h"

class GameInput : public IGameInput
{

public:


	/* メンバ関数 */

	// コンストラクタ
	GameInput(const Systems::IInput& input);

	// プレイヤーの移動入力を取得
	Math::Vector3 GetPlayerMove()         const override;
	// カメラの回転を取得
	Math::Vector2 GetPlayerCameraRotate() const override;


private:


	/* 定数 */

	// マウスの移動量倍率
	static constexpr float MOUSE_COEFFICIENT = 0.25f;


	/* メンバ変数 */

	const Systems::IInput& m_input;

};
