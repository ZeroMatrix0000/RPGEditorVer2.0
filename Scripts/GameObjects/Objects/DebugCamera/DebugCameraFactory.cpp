/*
 * FileName:     DebugCameraFactory.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * デバッグ用カメラ工場
 */

#include "Pch.h"
#include "DebugCameraFactory.h"

#include "Scripts/Commons/Renderings/CameraScreen.h"
#include "Scripts/Commons/GameObjects/GameObject.h"
#include "DebugCamera.h"

// デバッグ用カメラを作成
std::unique_ptr<GameObject> DebugCameraFactory::Create
(
	IComponentManager*                                    pIComponentManager,
	const Math::Vector2&                                  outputSize,
	Renderings::CameraScreen<Camera::EulerTargetCamera>** ppCameraScreen,
	DebugCamera**                                         ppDebugCamera
)
{
	std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>(pIComponentManager);
	auto* pCameraScreen = gameObject->AddComponent<Renderings::CameraScreen<Camera::EulerTargetCamera>>();
	pCameraScreen->SetCamera(Camera::EulerTargetCamera{ Math::Vector3::Zero, Math::Euler{ -30.0f, 0.0f, 0.0f }, 15.0f });
	pCameraScreen->SetProjectionMatrix(45.0f, outputSize);
	if (ppCameraScreen)
	{
		*ppCameraScreen = pCameraScreen;
	}
	auto* pDebugCamera = gameObject->AddComponent<DebugCamera>();
	pDebugCamera->SetPCameraScreen(pCameraScreen);
	if (ppDebugCamera)
	{
		*ppDebugCamera = pDebugCamera;
	}
	return gameObject;
}
