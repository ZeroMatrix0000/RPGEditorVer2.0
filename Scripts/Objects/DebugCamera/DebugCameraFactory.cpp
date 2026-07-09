/*
 * FileName:     DebugCamera.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/09
 *
 * デバッグ用カメラ工場
 */

#include "Pch.h"
#include "DebugCameraFactory.h"

#include "Scripts/Commons/Renderings/CameraScreen.h"
#include "Scripts/Commons/GameObjects/GameObject.h"
#include "DebugCamera.h"

// デバッグ用カメラを作成
void DebugCameraFactory::Create(const IComponentManager& iComponentManager, const Math::Vector2& outputSize, GameObject* pGameObject)
{
	auto* pCameraScreen = pGameObject->AddComponent<Renderings::CameraScreen<Camera::EulerTargetCamera>>(iComponentManager);
	pCameraScreen->SetCamera(Camera::EulerTargetCamera{ Math::Vector3::Zero, Math::Euler{ -30.0f, 0.0f, 0.0f }, 15.0f });
	pCameraScreen->SetProjectionMatrix(45.0f, outputSize);
	auto* pDebugCamera = pGameObject->AddComponent<DebugCamera>(iComponentManager);
	pDebugCamera->SetPCameraScreen(pCameraScreen);
}
