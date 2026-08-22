/*
 * FileName:     NPC.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/22
 *
 * NPC
 */

#include "Pch.h"
#include "NPC.h"

// コンストラクタ
NPC::NPC(const ComponentDesc& desc)
	: Component{ desc }
{
}

// 初期化処理
void NPC::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
}

// 更新処理
void NPC::Update(float elapsedTime)
{
}
