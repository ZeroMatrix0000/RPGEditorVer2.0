/*
 * FileName:     NPC.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/22
 *
 * NPC
 */

#pragma once

#include "Scripts/Commons/Components/Component.h"

// NPC
class NPC : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	NPC(const ComponentDesc& desc);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

	// 更新処理
	void Update(float elapsedTime);


private:

};
