/*
 * FileName:     CameraScreen.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
 *
 * カメラ画面
 */

#pragma once

#include "ICameraScreen.h"
#include "IModel3DRenderer.h"

namespace Renderings
{
	// カメラ画面
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
		CameraScreen(const ComponentCreatePermit& permit, GameObject* pOwner, IModel3DRenderer* pIModelRenderer)
			: ICameraScreen{ permit, pOwner }
			, m_camera{}
			, m_view{}
			, m_projection{}
			, m_pModels{}
			, m_pIModelRenderer{ pIModelRenderer }
		{
			// 描画者にカメラ画面を追加
			m_pIModelRenderer->AddPICameraScreen(this);
		}
		// デストラクタ
		~CameraScreen()
		{
			// 描画者からカメラ画面を削除
			m_pIModelRenderer->RemovePICameraScreen(this);
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

		// 画面に映すモデルのポインタリストを取得
		const std::unordered_set<const Model3D*>& GetPModels() const override { return m_pModels; }

		// モデルを追加
		void AddModel(const Model3D& model)
		{
			m_pModels.emplace(&model);
		}
		// モデルを削除
		void RemoveModel(const Model3D& model)
		{
			m_pModels.erase(&model);
		}

		// カメラを設定
		void SetCamera(const TCamera& camera) { m_camera = camera; }

		// プロジェクション行列を設定
		void SetProjectionMatrix(float viewAngle, const Math::Vector2& outputSize)
		{
			m_projection = Math::Matrix::CreatePerspectiveFieldOfView(Math::Deg2Rad(viewAngle), static_cast<float>(outputSize.x) / outputSize.y, 0.1f, 1000.0f);
		}


	private:


		/* メンバ変数 */

		// カメラ
		TCamera m_camera;

		// ビュー行列
		Math::Matrix m_view;
		// プロジェクション行列
		Math::Matrix m_projection;

		// 画面に映すモデルのポインタリスト
		std::unordered_set<const Model3D*> m_pModels;

		// モデル描画インタフェースのポインタ
		IModel3DRenderer* m_pIModelRenderer;

	};
}
