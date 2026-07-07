/*
 * FileName:     GameContext.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
 *
 * ゲームコンテキスト
 */

#pragma once

#include "Scripts/Commons/Systems/OnlyOne.h"
#include "Scripts/Commons/Systems/IWindowController.h"
#include "Scripts/Commons/Systems/IInput.h"
#include "Scripts/Commons/GameObjects/IComponentManager.h"
#include "Scripts/Commons/Scenes/ISceneManager.h"
#include "SceneTransitionData.h"

// ゲームコンテキスト
class GameContext : public Systems::OnlyOne
{

	typedef Scenes::ISceneManager<SceneTransitionData, GameContext> ISceneManager;


public:


	/* メンバ関数 */

	// コンストラクタ
	GameContext();

	// 初期化処理
	void Initialize
	(
		Systems::IWindowController* pIWindowController,
		Systems::IInput*            pIInput,
		IComponentManager*          pIComponentManager,
		ISceneManager*              pISceneManager
	);

	// ウィンドウ管理インタフェースを取得
	const Systems::IWindowController& GetIWindowController() const { return *m_pIWindowController; }
	// 入力管理インタフェースを取得
	const Systems::IInput& GetIInput() const { return *m_pIInput; }

	// コンポーネント工場を取得
	const IComponentManager& GetIComponentManager() const { return *m_pIComponentManager; }

	// シーン管理インタフェースを取得
	ISceneManager& GetISceneManager() const { return *m_pISceneManager; }


private:


	/* メンバ変数 */

	// ウィンドウ管理インタフェースのポインタ
	Systems::IWindowController* m_pIWindowController;
	// 入力管理インタフェースのポインタ
	Systems::IInput* m_pIInput;

	// コンポーネント管理インタフェースのポインタ
	IComponentManager* m_pIComponentManager;

	// シーン管理インタフェースのポインタ
	ISceneManager* m_pISceneManager;

};