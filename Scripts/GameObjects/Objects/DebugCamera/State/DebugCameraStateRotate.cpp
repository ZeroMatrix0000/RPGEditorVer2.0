/*
 * FileName:     DebugCameraStateRotate.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * デバッグ用カメラの待機状態
 */

#include "Pch.h"
#include "DebugCameraStateRotate.h"

#include "DebugCameraStateIdle.h"

 // コンストラクタ
DebugCameraStateRotate::DebugCameraStateRotate()
{
}

// 開始処理
void DebugCameraStateRotate::Enter(DebugCameraInternals* pInternals)
{
}

// 更新処理
void DebugCameraStateRotate::Update(DebugCameraInternals* pInternals, float elapsedTime)
{
	// カメラ
	Camera::EulerTargetCamera camera = pInternals->pCameraScreen->GetCamera();

	// 回転量
	Math::Vector2 rotate = pInternals->mouseMovement * MOUSE_COEFFICIENT;

	camera.rotation.y -= rotate.x;
	camera.rotation.x -= rotate.y;

	pInternals->pCameraScreen->SetCamera(camera);

	// 右クリックを離したら待機状態に戻る
	if (!pInternals->mouseButtonRight)
	{
		SetNextState(std::make_unique<DebugCameraStateIdle>());
	}
}

// 終了処理
void DebugCameraStateRotate::Exit(DebugCameraInternals* pInternals)
{
}
