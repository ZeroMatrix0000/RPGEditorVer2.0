/*
 * FileName:     TitleScene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * タイトルシーン
 */

#pragma once

#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Scenes/Scene.h"

class SceneTransitionData;
class GameContext;
class SelectMenu;

// サンプルシーン
class TitleScene : public Scenes::Scene<SceneTransitionData, GameContext>
{

	typedef Scene<SceneTransitionData, GameContext> Scene;


public:


	/* メンバ関数 */

	// コンストラクタ
	TitleScene(const ComponentCreatePermit& permit, GameObject* pOwner);

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

	// キャンバス
	GameObject m_canvas;

	// 選択メニュー
	GameObject m_selectMenu;
	// 選択メニューコンポーネント
	SelectMenu* m_pSelectMenu;

};
