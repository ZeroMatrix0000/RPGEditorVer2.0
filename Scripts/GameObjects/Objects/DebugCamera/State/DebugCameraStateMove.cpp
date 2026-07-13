/*
 * FileName:     DebugCameraStateMove.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * デバッグ用カメラの待機状態
 */

#include "Pch.h"
#include "DebugCameraStateMove.h"

#include "DebugCameraStateIdle.h"

 // コンストラクタ
DebugCameraStateMove::DebugCameraStateMove()
{
}

// 開始処理
void DebugCameraStateMove::Enter(DebugCameraInternals* pInternals)
{
}

// 更新処理
void DebugCameraStateMove::Update(DebugCameraInternals* pInternals, float elapsedTime)
{
	// カメラ
	Camera::EulerTargetCamera camera = pInternals->pCameraScreen->GetCamera();

	// マウスの移動量の移動量
	Math::Vector2 mouseDelta = pInternals->mouseMovement * MOUSE_COEFFICIENT * camera.distance;
	// カメラの移動
	Math::Vector3 movement = Math::Vector3::Transform
	(
		Math::Vector3{ -mouseDelta.x, mouseDelta.y, 0.0f },
		camera.rotation.CreateQuaternion()
	);
	camera.position += movement;

	pInternals->pCameraScreen->SetCamera(camera);

	// 中クリックを離したら待機状態に戻る
	if (!pInternals->mouseButtonMiddle)
	{
		SetNextState(std::make_unique<DebugCameraStateIdle>());
	}
}

// 終了処理
void DebugCameraStateMove::Exit(DebugCameraInternals* pInternals)
{
}
