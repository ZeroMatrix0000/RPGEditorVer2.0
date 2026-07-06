/*
 * FileName:     Model3DRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 3Dモデル描画
 */

#pragma once

#include "IModel3DRenderer.h"

namespace Systems
{
	class IResources;
}

namespace Renderings
{
	// 3Dモデル描画
	class Model3DRenderer : public IModel3DRenderer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Model3DRenderer(const Systems::IResources& iResources);

		// 初期化処理
		void Initialize(ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates);
		// 描画処理
		void Render();

		// カメラ画面インタフェースのポインタを追加
		void AddPICameraScreen(const ICameraScreen* pICameraScreen) override;
		// カメラ画面インタフェースのポインタを削除
		void RemovePICameraScreen(const ICameraScreen* pICameraScreen) override;


	private:


		/* メンバ変数 */

		// カメラ画面のポインタリスト
		std::unordered_set<const ICameraScreen*> m_pICameraScreens;

		// コンテキストのポインタ
		ID3D11DeviceContext4* m_pContext;
		// コモンステートのポインタ
		const DirectX::CommonStates* m_pCommonStates;

		// リソースのインタフェースの参照
		const Systems::IResources& m_refIResources;

	};
}
