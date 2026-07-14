/*
 * FileName:     GameContext.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * ゲームコンテキスト
 */

#pragma once

#include "Scripts/Commons/Systems/OnlyOne.h"
#include "SceneTransitionData.h"

namespace Systems
{
	class IWindowController;
	class IInput;
}
namespace GameObjects
{
	class IGameObjectManager;
}
namespace Components
{
	class IComponentManager;
}
namespace Scenes
{
	template<typename TTransitionData, typename TContext>
	class ISceneManager;
}
class IJsonManager;

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
		IGameObjectManager*         pIGameObjectManager,
		ISceneManager*              pISceneManager
	);

	// ウィンドウ管理インタフェースを取得
	Systems::IWindowController* GetPIWindowController() const { return m_pIWindowController; }
	// 入力管理インタフェースを取得
	Systems::IInput* GetPIInput() const { return m_pIInput; }

	// コンポーネント工場を取得
	IComponentManager* GetPIComponentManager() const { return m_pIComponentManager; }
	// コンポーネント工場を取得
	IGameObjectManager* GetPIGameObjectManager() const { return m_pIGameObjectManager; }

	// シーン管理インタフェースを取得
	ISceneManager* GetPISceneManager() const { return m_pISceneManager; }


private:


	/* メンバ変数 */

	// ウィンドウ管理インタフェースのポインタ
	Systems::IWindowController* m_pIWindowController;
	// 入力管理インタフェースのポインタ
	Systems::IInput* m_pIInput;

	// コンポーネント管理インタフェースのポインタ
	IComponentManager* m_pIComponentManager;
	// ゲームオブジェクト管理インタフェースのポインタ
	IGameObjectManager* m_pIGameObjectManager;

	// シーン管理インタフェースのポインタ
	ISceneManager* m_pISceneManager;

};