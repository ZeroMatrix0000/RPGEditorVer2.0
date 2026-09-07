/*
 * FileName:     GamePlaySceneStateEvent.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/06
 *
 * ゲームプレイシーンのイベント状態
 */

#include "Pch.h"
#include "GamePlaySceneStateEvent.h"

#include "../GamePlaySceneInternals.h"
#include "GamePlaySceneStates.h"
#include "Scripts/GameObjects/Objects/Player/Player.h"
#include "Scripts/GameObjects/Objects/Player/PlayerCamera.h"
#include "Scripts/GameObjects/Objects/NPC/NPC.h"
#include "Scripts/GameObjects/Objects/NPC/NPCManager.h"
#include "Scripts/GameObjects/UIs/Z2Talk/Z2Talk.h"
#include "Scripts/Main/GameContext.h"
#include "Scripts/Main/IGameInput.h"
#include "Scripts/Commons/Colliders/MeshCollider.h"

// コンストラクタ
GamePlaySceneStateEvent::GamePlaySceneStateEvent()
{
}

// 開始処理
void GamePlaySceneStateEvent::Enter(GamePlaySceneInternals* pInternals)
{
	// カーソルを隠す
	pInternals->pNPCManager->HideCursor(true);
}

// 更新処理
void GamePlaySceneStateEvent::Update(GamePlaySceneInternals* pInternals, float elapsedTime)
{
	// NPCの更新
	pInternals->pNPCManager->SetRotation(pInternals->pPlayer->GetPosition());
	pInternals->pNPCManager->Update(elapsedTime);
	pInternals->pNPCManager->SetCursor(*pInternals->pCameraScreen);

	// ゲーム入力
	auto* pIGameInput = pInternals->gameContext.GetPIGameInput();

	// プレイヤーの更新
	RotatePlayer(pInternals);
	pInternals->pPlayer->Update(elapsedTime, Math::Vector3::Zero, false, false);
	pInternals->pPlayer->BoxCorrect(pInternals->pNPCManager->GetPBoxes());
	pInternals->pPlayer->MeshCorrect(pInternals->pGround->GetWorldMesh());

	// はなすの更新
	pInternals->pZ2Talk->SetPosition(pInternals->pPlayer->GetBox(), *pInternals->pCameraScreen);
	pInternals->pZ2Talk->Update(elapsedTime, false);

	// カメラの更新
	pInternals->pPlayerCamera->MeshCorrect(pInternals->pGround->GetWorldMesh(), pInternals->pPlayer->GetPosition());
	pInternals->pPlayerCamera->Update(elapsedTime);
	pInternals->pCameraScreen->UpdateViewMatrix();
}

// 終了処理
void GamePlaySceneStateEvent::Exit(GamePlaySceneInternals* pInternals)
{
	// カーソルを表示
	pInternals->pNPCManager->HideCursor(false);
}

// プレイヤーを会話相手の方に向ける
void GamePlaySceneStateEvent::RotatePlayer(GamePlaySceneInternals* pInternals)
{
	// プレイヤーを会話相手の方に向ける
	// 向く方向
	Math::Vector3 direction = pInternals->pNPCManager->GetPFocusedNPC()->GetBox().position - pInternals->pPlayer->GetPosition();
	// Y軸方向は無視
	direction.y = 0.0f;
	// 正規化
	direction.Normalize();
	// 回転
	Math::Quaternion rotation = Math::Quaternion::FromToRotation(Math::Vector3::Backward, direction);
	pInternals->pPlayer->SetRotation(rotation);
}
