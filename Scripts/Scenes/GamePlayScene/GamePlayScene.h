/*
 * FileName:     GamePlayScene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/22
 *
 * ゲームプレイシーン
 */

#pragma once

#include "Scripts/Commons/Scenes/Scene.h"

namespace Renderings
{
	class ICameraScreen;
	class Canvas;
}
namespace Colliders
{
	class BoxCollider;
	class MeshCollider;
}
class SceneTransitionData;
class GameContext;
class Player;
class PlayerCamera;
class NPCManager;

// ゲームプレイシーン
class GamePlayScene : public Scenes::Scene<SceneTransitionData, GameContext>
{

	typedef Scene<SceneTransitionData, GameContext> Scene;


public:


	/* メンバ関数 */

	// コンストラクタ
	GamePlayScene(const ComponentDesc& desc);

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

	// プレイヤー
	Player* m_pPlayer;
	// プレイヤーカメラ
	PlayerCamera* m_pPlayerCamera;

	// NPC管理
	NPCManager* m_pNPCManager;

	// 地面
	Colliders::MeshCollider* m_pGround;

	// カメラ画面
	Renderings::ICameraScreen* m_pCameraScreen;

	// キャンバス
	Renderings::Canvas* m_pCanvas;

};
