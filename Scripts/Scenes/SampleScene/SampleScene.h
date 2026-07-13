/*
 * FileName:     SampleScene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * サンプルシーン
 */

#pragma once

#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Scenes/Scene.h"

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
class SceneTransitionData;
class GameContext;
class DebugCamera;

// サンプルシーン
class SampleScene : public Scenes::Scene<SceneTransitionData, GameContext>
{

	typedef Scene<SceneTransitionData, GameContext> Scene;


public:


	/* メンバ関数 */

	// コンストラクタ
	SampleScene(const ComponentCreatePermit& permit, GameObject* pOwner);

	// 初期化処理
	void Initialize(const SceneTransitionData& data) override;
	// 更新処理
	void Update(float elapsedTime) override;
	// 終了処理
	void Finalize() override;

	// メッセージを受け取る
	void AcceptMessage(const std::string& message) override;


private:


	/* メンバ変数 */

	// テスト
	GameObject m_test3D;
	// テスト
	GameObject m_test2D;
	// テスト
	GameObject m_test2D2;

	// 地面
	GameObject m_ground;

	// カメラ
	GameObject m_camera;
	// カメラ画面
	Renderings::CameraScreen<Camera::EulerTargetCamera>* m_pCameraScreen;
	// デバッグカメラ
	DebugCamera* m_pDebugCamera;

	// キャンバス
	GameObject m_canvas;

};
