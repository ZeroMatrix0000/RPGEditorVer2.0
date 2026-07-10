/*
 * FileName:     CameraScreen.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * カメラ画面
 */

#pragma once

#include "ICameraScreen.h"
#include "IModel3DRenderer.h"

namespace Renderings
{
	// カメラ画面
	template<typename TCamera> requires IsSame
	<
		TCamera,
		Camera::QuaternionCamera,
		Camera::QuaternionTargetCamera,
		Camera::EulerCamera,
		Camera::EulerTargetCamera
	>
	class CameraScreen : public ICameraScreen
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		CameraScreen(const ComponentCreatePermit& permit, GameObject* pOwner)
			: ICameraScreen{ permit, pOwner }
			, m_camera{}
			, m_view{}
			, m_projection{}
		{
		}
		// デストラクタ
		~CameraScreen()
		{
		}

		// ビュー行列を更新
		void UpdateViewMatrix()
		{
			m_view = m_camera.CreateViewMatrix();
		}

		// ビュー行列を取得
		const Math::Matrix& GetViewMatrix() const override { return m_view; }
		// プロジェクション行列を取得
		const Math::Matrix& GetProjectionMatrix() const override { return m_projection; }

		// 目の座標を取得
		const Math::Vector3 GetEyePosition() const override { return m_camera.GetEyePosition(); }

		// カメラを設定
		void SetCamera(const TCamera& camera) { m_camera = camera; }

		// プロジェクション行列を設定
		void SetProjectionMatrix(float viewAngle, const Math::Vector2& outputSize)
		{
			m_projection = Math::Matrix::CreatePerspectiveFieldOfView
			(
				Math::Deg2Rad(viewAngle),
				static_cast<float>(outputSize.x) / outputSize.y,
				0.1f,
				1000.0f
			);
		}

		// カメラを取得
		const TCamera& GetCamera() const { return m_camera; }


	private:


		/* メンバ変数 */

		// カメラ
		TCamera m_camera;

		// ビュー行列
		Math::Matrix m_view;
		// プロジェクション行列
		Math::Matrix m_projection;

	};
}
