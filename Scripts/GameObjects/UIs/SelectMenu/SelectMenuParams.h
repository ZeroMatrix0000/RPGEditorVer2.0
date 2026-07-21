/*
 * FileName:     SelectMenuParams.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
 *
 * 選択メニューのパラメータ
 */

#pragma once

struct SelectMenuParams
{

	/* メンバ変数 */

	// 幅
	float width{};
	// 高さ
	float height{};

	// 間隔
	float interval{};

	// 基準座標
	Math::Vector2 basePosition{};

	// カーソルの移動時間
	float cursorMoveTime{};
	// カーソルのイージング補間方法
	Easing::Type cursorEasingType{};
	// カーソルのイージングインアウト
	Easing::InOut cursorEasingInOut{};
	// カーソルの左右の揺れの大きさ
	float cursorSwaySize{};

};
