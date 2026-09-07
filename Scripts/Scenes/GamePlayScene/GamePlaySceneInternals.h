/*
 * FileName:     GamePlaySceneInternals.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/07
 *
 * ゲームプレイシーンの内部データ
 */

#pragma once

#include "Scripts/Commons/Systems/State.h"

namespace GameObjects
{
	class GameObject;
}
namespace Colliders
{
	class MeshCollider;
}
namespace Renderings
{
	class ICameraScreen;
	class Canvas;
}
class GameContext;
class Player;
class PlayerCamera;
class NPCManager;
class Z2Talk;

// ゲームプレイシーンの内部データ
struct GamePlaySceneInternals
{

	/* メンバ関数 */

	// コンストラクタ
	GamePlaySceneInternals(std::vector<std::unique_ptr<GameObject>>* pGameObjects, const GameContext& gameContext)
		: pGameObjects{ pGameObjects }
		, gameContext{ gameContext }
		, pPlayer{}
		, pPlayerCamera{}
		, pNPCManager{}
		, pGround{}
		, pZ2Talk{}
		, pCameraScreen{}
		, pCanvas{}
	{
	}


	/* メンバ変数 */

	// ゲームオブジェクトリスト
	std::vector<std::unique_ptr<GameObject>>* pGameObjects;
	// ゲームコンテキスト
	const GameContext& gameContext;

	// プレイヤー
	Player* pPlayer;
	// プレイヤーカメラ
	PlayerCamera* pPlayerCamera;

	// NPC管理
	NPCManager* pNPCManager;

	// 地面
	Colliders::MeshCollider* pGround;

	// Z: はなす
	Z2Talk* pZ2Talk;

	// カメラ画面
	Renderings::ICameraScreen* pCameraScreen;

	// キャンバス
	Renderings::Canvas* pCanvas;

};
