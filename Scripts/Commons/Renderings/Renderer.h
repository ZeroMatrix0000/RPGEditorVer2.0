/*
 * FileName:     Renderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
 *
 * 描画
 */

#pragma once

#include "Model3DRenderer.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "../Systems/OnlyOne.h"

namespace Systems
{
	class IResources;
}

namespace Renderings
{
	// 画像描画
	class Renderer : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Renderer(const Systems::IResources& iResources);

		// 初期化処理
		void Initialize
		(
			ID3D11DeviceContext4*        pContext,
			IDXGISwapChain4*             pSwapChain,
			const DirectX::CommonStates& commonStates
		);
		// 描画処理
		void Render();

		// テキスト描画のリセット
		void ResetTextRenderer();
		// テキスト描画の初期化
		void InitializeTextRenderer(IDXGISwapChain4* pSwapChain);

		// モデル描画インタフェースを取得
		Renderings::IModel3DRenderer& GetIModelRenderer() { return m_modelRenderer; }
		// 画像描画インタフェースを取得
		Renderings::IImageRenderer&   GetIImageRenderer() { return m_imageRenderer; }
		// テキスト描画インタフェースを取得
		Renderings::ITextRenderer&    GetITextRenderer()  { return m_textRenderer; }


	private:


		/* メンバ変数 */

		// モデル描画
		Renderings::Model3DRenderer m_modelRenderer;
		// 画像描画
		Renderings::ImageRenderer   m_imageRenderer;
		// テキスト描画
		Renderings::TextRenderer    m_textRenderer;

	};
}
