/*
 * FileName:     Model3D.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * 3Dモデル
 */

#pragma once

#include "../GameObjects/Component.h"

namespace Renderings
{
	class ICameraScreen;
	class IModel3DRenderer;

	// 3Dモデル
	class Model3D : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Model3D(const ComponentCreatePermit& permit, GameObject* pOwner, IModel3DRenderer* pIModelRenderer);
		// デストラクタ
		~Model3D();

		// モデルソース名を設定
		void SetModelSourceName(const std::string& modelSourceName) { m_modelSourceName = modelSourceName; }

		// 映るカメラ画面を追加
		void AddICameraScreen(const ICameraScreen& iCameraScreen);
		// 映るカメラ画面を削除
		void RemoveICameraScreen(const ICameraScreen& iCameraScreen);

		// モデルソース名を取得
		const std::string& GetModelSourceName() const { return m_modelSourceName; }

		// 映るカメラ画面のポインタリストを取得
		const std::unordered_set<const ICameraScreen*>& GetPICameraScreens() const { return m_pICameraScreens; }


	private:


		/* メンバ変数 */

		// モデルソース名
		std::string m_modelSourceName;

		// 映るカメラ画面のポインタリスト
		std::unordered_set<const ICameraScreen*> m_pICameraScreens;

		// モデル描画インタフェースのポインタ
		IModel3DRenderer* m_pIModelRenderer;

	};
}
