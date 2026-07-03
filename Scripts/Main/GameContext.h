/*
 * FileName:     GameContext.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * ゲームコンテキスト
 */

#pragma once

#include "Scripts/Commons/Systems/OnlyOne.h"
#include "Scripts/Commons/Systems/IWindowController.h"
#include "Scripts/Commons/GameObjects/ComponentFactory.h"
#include "Scripts/Commons/Scenes/ISceneManager.h"
#include "SceneTransitionData.h"

class GameContext : public Systems::OnlyOne
{

public:


	/* メンバ関数 */

	// コンストラクタ
	GameContext();

	// 初期化処理
	void Initialize
	(
		Systems::IWindowController* pIWindowController,
		ComponentFactory* pComponentFactory,
		Scenes::ISceneManager<SceneTransitionData>* pISceneManager
	);

	// ウィンドウ管理インタフェースを取得
	const Systems::IWindowController& GetIWindowController() const { return *m_pIWindowController; }

	// コンポーネント工場を取得
	const ComponentFactory& GetComponentFactory() const { return *m_pComponentFactory; }

	// シーン管理インタフェースを取得
	Scenes::ISceneManager<SceneTransitionData>& GetISceneManager() const { return *m_pISceneManager; }


private:


	/* メンバ変数 */

	// ウィンドウ管理インタフェースのポインタ
	Systems::IWindowController* m_pIWindowController;

	// コンポーネント工場のポインタ
	ComponentFactory* m_pComponentFactory;

	// シーン管理インタフェースのポインタ
	Scenes::ISceneManager<SceneTransitionData>* m_pISceneManager;

};