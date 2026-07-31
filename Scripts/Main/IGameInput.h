/*
 * FileName:     IGameInput.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/31
 *
 * ゲーム入力のインタフェース
 */

#pragma once

#include "../Commons/Systems/OnlyOne.h"

class IGameInput : public Systems::OnlyOne
{

public:


	/* メンバ関数 */

	// コンストラクタ
	IGameInput()
		: OnlyOne{ typeid(IGameInput) }
	{
	}

	// プレイヤーの移動入力を取得
	virtual Math::Vector3 GetPlayerMove()         const = 0;
	// プレイヤーのカメラの回転入力を取得
	virtual Math::Vector2 GetPlayerCameraRotate() const = 0;

};
