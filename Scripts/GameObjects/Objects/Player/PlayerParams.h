/*
 * FileName:     PlayerParams.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
 *
 * プレイヤーのパラメータ
 */

#pragma once

struct PlayerParams
{

	/* メンバ変数 */

	// 移動の速さの最大
	float moveMaxSpeed{};
	// 移動加速度
	float moveAcceleration{};

	// 落下加速度
	float fallAcceleration;

	// カメラの速度の参照量
	float cameraVelocityCoefficient{};

};
