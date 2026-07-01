/*
 * FileName:     Game.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * ゲーム
 */

#pragma once

#include "Scripts/Commons/Systems/OnlyOne.h"
#include "Scripts/Commons/Renderings/DeviceResources.h"
#include "Scripts/Commons/Renderings/RenderingResources.h"
#include "Scripts/Commons/Systems/Resources.h"
#include "Scripts/Commons/GameObjects/ComponentFactory.h"
#include "Scripts/Commons/Scenes/SceneManager.h"
#include "SceneTransitionData.h"
#include "GameContext.h"

class Game : public Systems::OnlyOne
{

public:


	/* メンバ関数 */

	// コンストラクタ
	Game();

	// 初期化処理
	void Initialize(const HWND& hWindow);
	// 終了処理
	void Finalize();

	// 毎フレーム呼ぶ処理
	void Tick();

	// ウィンドウサイズ変更時の処理
	void OnWindowSizeChanged(const Math::Vector2Int& outputSize);

private:


	/* メンバ関数 */

	// 更新処理
	void Update();
	// 描画処理
	void Render();

	// リソースの追加
	void AddResources(ID3D11Device5* device, DirectX::EffectFactory* fx);


	/* メンバ変数 */

	// ウィンドウハンドル
	HWND m_hWindow;

	// デバイスリソース
	Renderings::DeviceResources m_deviceResources;
	// 描画リソース
	Renderings::RenderingResources m_renderingResources;

	// リソース
	Systems::Resources m_resources;

	// コンポーネント作成
	ComponentFactory m_componentFactory;

	// シーン管理
	Scenes::SceneManager<SceneTransitionData, GameContext> m_sceneManager;

	// ゲームコンテキスト
	GameContext m_context;

};