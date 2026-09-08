/*
 * FileName:     ActionManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/08
 *
 * アクション管理
 */

#pragma once

#include "Scripts/Commons/Components/Component.h"

namespace Systems
{
	class IResources;
}

// 長方形の当たり判定
class ActionManager : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	ActionManager(const ComponentDesc& desc, const Systems::IResources& iResources);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

	// イベントを設定
	void LoadEvent(const std::string& eventName);


private:


	/* メンバ変数 */

	// アクション数
	size_t m_eventCount;
	// 現在のアクション番号
	size_t m_eventIndex;

	// イベント
	const nlohmann::ordered_json* m_pEvent;

	// リソース管理
	const Systems::IResources& m_refIResources;

};
