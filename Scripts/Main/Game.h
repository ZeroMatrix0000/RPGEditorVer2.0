/*
 * FileName:     Game.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * ゲーム
 */

#pragma once

#include "Scripts/Commons/Renderings/DeviceResources.h"
#include "Scripts/Commons/Systems/OnlyOne.h"
#include "Scripts/Commons/Systems/ComponentFactory.h"

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


	/* メンバ変数 */

	// ウィンドウハンドル
	HWND m_hWindow;

	// デバイスリソース
	Renderings::DeviceResources m_deviceResources;

	// コンポーネント作成
	Systems::ComponentFactory m_componentFactory;

};