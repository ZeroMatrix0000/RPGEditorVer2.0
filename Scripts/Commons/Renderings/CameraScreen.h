/*
 * FileName:     CameraScreen.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * カメラ画面
 */

#pragma once

#include "ICameraScreen.h"

namespace Renderings
{
	template<typename TCamera> requires
		std::same_as<TCamera, Camera::QuaternionCamera>       ||
		std::same_as<TCamera, Camera::QuaternionTargetCamera> ||
		std::same_as<TCamera, Camera::EulerCamera>            ||
		std::same_as<TCamera, Camera::EulerTargetCamera>
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

		// 更新処理
		void Update(float elapsedTime) override
		{
			m_view = m_camera.CreateViewMatrix();
		}

		// ビュー行列を取得
		const Math::Matrix& GetViewMatrix() const override { return m_view; }
		// プロジェクション行列を取得
		const Math::Matrix& GetProjectionMatrix() const override { return m_projection; }

		// プロジェクション行列を設定
		void SetProjectionMatrix(float viewAngle, const Math::Vector2& outputSize)
		{
			m_projection = Math::Matrix::CreatePerspectiveFieldOfView(Math::Deg2Rad(viewAngle), static_cast<float>(outputSize.x) / outputSize.y, 0.1f, 1000.0f);
		}

		// カメラの参照を取得
		TCamera& GetRefCamera() { return m_camera; }


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
