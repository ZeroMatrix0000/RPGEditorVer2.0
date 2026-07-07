/*
 * FileName:     SampleScene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * サンプルシーン
 */

#pragma once

#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Scenes/Scene.h"
#include "Scripts/Main/SceneTransitionData.h"
#include "Scripts/Main/GameContext.h"

// サンプルシーン
class SampleScene : public Scenes::Scene<SceneTransitionData, GameContext>
{

	typedef Scene<SceneTransitionData, GameContext> Scene;


public:


	/* メンバ関数 */

	// コンストラクタ
	SampleScene(const ComponentCreatePermit& permit, GameObject* pOwner);

	// 初期化処理
	void Initialize(const SceneTransitionData& data) override;
	// 更新処理
	void Update(float elapsedTime) override;
	// 終了処理
	void Finalize() override;

	// メッセージを受け取る
	void AcceptMessage(const std::string& message) override;


private:


	/* メンバ変数 */

	// テスト
	GameObject m_test3D;
	// テスト
	GameObject m_test2D;
	// テスト
	GameObject m_test2D2;

	// カメラ
	GameObject m_camera;

	// キャンバス
	GameObject m_canvas;

};
