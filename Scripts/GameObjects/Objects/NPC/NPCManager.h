/*
 * FileName:     NPCManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/22
 *
 * NPC管理
 */

#pragma once

#include "NPC.h"
#include "Scripts/Commons/Components/Component.h"

namespace Renderings
{
	class ICameraScreen;
}

// NPC管理
class NPCManager : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	NPCManager(const ComponentDesc& desc);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

	// 更新処理
	void Update(float elapsedTime);


private:


	/* メンバ変数 */

	// NPCリスト
	std::unordered_set<NPC*> m_pNPCList;

};
