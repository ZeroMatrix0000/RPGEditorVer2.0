/*
 * FileName:     GamePlaySceneStateEvent.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/06
 *
 * ゲームプレイシーンのイベント状態
 */

#pragma once

#include "Scripts/Commons/Systems/State.h"

struct GamePlaySceneInternals;

// ゲームプレイシーンのイベント状態
class GamePlaySceneStateEvent : public Systems::State<GamePlaySceneInternals>
{

public:


	/* メンバ関数 */

	// コンストラクタ
	GamePlaySceneStateEvent();

	// 開始処理
	void Enter(GamePlaySceneInternals* pInternals) override;
	// 更新処理
	void Update(GamePlaySceneInternals* pInternals, float elapsedTime) override;
	// 終了処理
	void Exit(GamePlaySceneInternals* pInternals) override;

};
