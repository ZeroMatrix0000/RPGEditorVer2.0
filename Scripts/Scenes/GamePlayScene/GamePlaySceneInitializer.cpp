/*
 * FileName:     GamePlaySceneInitializer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/07
 *
 * ゲームプレイシーンの初期化関数
 */

#include "Pch.h"
#include "GamePlaySceneInitializer.h"

#include "GamePlaySceneInternals.h"
#include "Scripts/GameObjects/Objects/Player/Player.h"
#include "Scripts/GameObjects/Objects/Player/PlayerCamera.h"
#include "Scripts/GameObjects/Objects/NPC/NPCManager.h"
#include "Scripts/GameObjects/UIs/Z2Talk/Z2Talk.h"
#include "Scripts/Main/GameContext.h"
#include "Scripts/Commons/GameObjects/IGameObjectManager.h"
#include "Scripts/Commons/Colliders/MeshCollider.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/Systems/IInput.h"
#include "Scripts/Commons/Systems/IWindowController.h"

void GamePlaySceneInitializer::operator()(GamePlaySceneInternals* pInternals) const
{
	// マウスをループ
	pInternals->gameContext.GetPIInput()->SetMousePositionLoop(true);

	// 出力サイズ
	const Math::Vector2& outputSize = pInternals->gameContext.GetPIWindowController()->GetOutputSize();

	// ゲームオブジェクト管理
	auto* pIGameObjectManager = pInternals->gameContext.GetPIGameObjectManager();

	pIGameObjectManager->SetPGameObjects(pInternals->pGameObjects);
	pIGameObjectManager->Load("Scene_GamePlay");

	// プレイヤーを取得
	pInternals->pPlayer = pIGameObjectManager->Find("Player")->GetComponent<Player>();

	// プレイヤーカメラを取得
	GameObject* pCamera = pIGameObjectManager->Find("PlayerCamera");
	pInternals->pCameraScreen = pCamera->GetComponent<Renderings::ICameraScreen>();
	pInternals->pCameraScreen->UpdateViewMatrix();
	pInternals->pCameraScreen->SetProjectionMatrix(outputSize);
	pInternals->pPlayerCamera = pCamera->GetComponent<PlayerCamera>();

	// キャンバスを取得
	pInternals->pCanvas = pIGameObjectManager->Find("Canvas")->GetComponent<Renderings::Canvas>();
	pInternals->pCanvas->SetSize(outputSize);

	// NPCマネージャーを取得
	pInternals->pNPCManager = pIGameObjectManager->Find("NPCManager")->GetComponent<NPCManager>();

	// 地面を取得
	pInternals->pGround = pIGameObjectManager->Find("Ground")->GetComponent<Colliders::MeshCollider>();
	pInternals->pGround->ApplyTransform();

	// はなすを取得
	pInternals->pZ2Talk = pIGameObjectManager->Find("Z2Talk")->GetComponent<Z2Talk>();
}
