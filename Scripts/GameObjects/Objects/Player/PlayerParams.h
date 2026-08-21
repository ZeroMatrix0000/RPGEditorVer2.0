/*
 * FileName:     PlayerParams.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/21
 *
 * プレイヤーのパラメータ
 */

#pragma once

struct PlayerParams
{

	/* メンバ変数 */

	// 移動加速度
	float moveAcceleration{};
	// ダッシュ時の速度倍率
	float dashRatio{};

	// 落下加速度
	float fallAcceleration;

	// カメラの速度の参照量
	float cameraVelocityCoefficient{};

};
