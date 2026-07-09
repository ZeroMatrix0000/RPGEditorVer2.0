/*
 * FileName:     DebugCamera.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/09
 *
 * デバッグ用カメラ工場
 */

#pragma once

namespace GameObjects
{
	class GameObject;
	class IComponentManager;
}

// デバッグ用カメラ工場
namespace DebugCameraFactory
{
	// デバッグ用カメラを作成
	void Create(const IComponentManager& iComponentManager, const Math::Vector2& outputSize, GameObject* pGameObject);
}
