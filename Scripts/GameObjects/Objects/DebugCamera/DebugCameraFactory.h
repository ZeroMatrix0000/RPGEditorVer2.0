/*
 * FileName:     DebugCameraFactory.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * デバッグ用カメラ工場
 */

#pragma once

namespace Renderings
{
	template<typename TCamera> requires IsSame
	<
		TCamera,
		Camera::QuaternionCamera,
		Camera::QuaternionTargetCamera,
		Camera::EulerCamera,
		Camera::EulerTargetCamera
	>
	class CameraScreen;
}
namespace GameObjects
{
	class GameObject;
}
namespace Components
{
	class IComponentManager;
}
class DebugCamera;

// デバッグ用カメラ工場
namespace DebugCameraFactory
{
	// デバッグ用カメラを作成
	std::unique_ptr<GameObject> Create
	(
		IComponentManager*                                    pIComponentManager,
		const Math::Vector2&                                  outputSize,
		Renderings::CameraScreen<Camera::EulerTargetCamera>** ppCameraScreen,
		DebugCamera**                                         ppDebugCamera
	);
}
