/*
 * FileName:     Model3D.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * 3Dモデル
 */

#pragma once

#include "../GameObjects/Component.h"

namespace Renderings
{
	// 前方宣言
	class ICameraScreen;
	class IModel3DRenderer;

	class Model3D : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Model3D(const ComponentCreatePermit& permit, GameObject* pOwner, IModel3DRenderer* pIModelRenderer);
		// デストラクタ
		~Model3D();

		// モデル名を設定
		void SetModelSourceName(const std::string& modelSourceName) { m_modelSourceName = modelSourceName; }
		// カメラ画面インタフェースを設定
		void SetICameraScreen(const ICameraScreen& iCameraScreen) { m_pICameraScreen = &iCameraScreen; }

		// モデル名を取得
		const std::string& GetModelSourceName() const { return m_modelSourceName; }
		// カメラ画面インタフェースを取得
		const ICameraScreen* GetPICameraScreen() const { return m_pICameraScreen; }


	private:


		/* メンバ変数 */

		// モデルソース名
		std::string m_modelSourceName;

		// モデル描画インタフェースのポインタ
		IModel3DRenderer* m_pIModelRenderer;

		// カメラ画面インタフェースのポインタ
		const ICameraScreen* m_pICameraScreen;

	};
}
