/*
 * FileName:     DebugCameraStateIdle.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * デバッグ用カメラの待機状態
 */

#include "Pch.h"
#include "DebugCameraStateIdle.h"

#include "DebugCameraStateRotate.h"
#include "DebugCameraStateMove.h"

// コンストラクタ
DebugCameraStateIdle::DebugCameraStateIdle()
{
}

// 開始処理
void DebugCameraStateIdle::Enter(DebugCameraInternals* pInternals)
{
}

// 更新処理
void DebugCameraStateIdle::Update(DebugCameraInternals* pInternals, float elapsedTime)
{
	// カメラ
	Camera::EulerTargetCamera camera = pInternals->pCameraScreen->GetCamera();

	// マウスホイールでカメラの距離を変更
	float ratio = Math::Pow(WHEEL_COEFFICIENT, static_cast<float>(-pInternals->mouseWheelDelta));
	camera.distance *= ratio;
	if (camera.distance < Math::EPSILON)
	{
		camera.distance = Math::EPSILON;
	}

	pInternals->pCameraScreen->SetCamera(camera);

	// 右クリックで回転状態に遷移
	if (pInternals->mouseButtonRight)
	{
		SetNextState(std::make_unique<DebugCameraStateRotate>());
	}
	// 中クリックで移動状態に遷移
	if (pInternals->mouseButtonMiddle)
	{
		SetNextState(std::make_unique<DebugCameraStateMove>());
	}
}

// 終了処理
void DebugCameraStateIdle::Exit(DebugCameraInternals* pInternals)
{
}
