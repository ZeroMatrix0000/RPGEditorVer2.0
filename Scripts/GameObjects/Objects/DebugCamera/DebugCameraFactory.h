/*
 * FileName:     DebugCameraFactory.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
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
	class IComponentManager;
}
class DebugCamera;

// デバッグ用カメラ工場
namespace DebugCameraFactory
{
	// デバッグ用カメラを作成
	void Create
	(
		const IComponentManager&                              iComponentManager,
		const Math::Vector2&                                  outputSize,
		GameObject*                                           pGameObject,
		Renderings::CameraScreen<Camera::EulerTargetCamera>** ppCameraScreen,
		DebugCamera**                                         ppDebugCamera
	);
}
