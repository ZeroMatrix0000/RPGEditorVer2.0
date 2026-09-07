/*
 * FileName:     MessageWindow.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/07
 *
 * メッセージウィンドウ
 */

#pragma once

#include "Scripts/Commons/Components/Component.h"

// メッセージウィンドウ
class MessageWindow : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	MessageWindow(const ComponentDesc& desc);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;


private:


};
