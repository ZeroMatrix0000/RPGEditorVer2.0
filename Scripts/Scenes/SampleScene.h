/*
 * FileName:     SampleScene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * サンプルシーン
 */

#pragma once

#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Scenes/Scene.h"
#include "Scripts/Main/SceneTransitionData.h"
#include "Scripts/Main/GameContext.h"

class SampleScene : public Scenes::Scene<SceneTransitionData, GameContext>
{

	typedef Scene<SceneTransitionData, GameContext> Scene;


public:


	/* メンバ関数 */

	// コンストラクタ
	SampleScene(const ComponentCreatePermit& permit);

	// 初期化処理
	void Initialize(const SceneTransitionData& data) override;


private:


	/* メンバ変数 */

	// テスト
	GameObject m_test;

};
