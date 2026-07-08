/*
 * FileName:     Renderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * 描画
 */

#pragma once

#include "Model3DRenderer.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "ColliderRenderer.h"
#include "../Systems/OnlyOne.h"

namespace Systems
{
	class IResources;
}

namespace Renderings
{
	// 描画
	class Renderer : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Renderer(const Systems::IResources& iResources);

		// 初期化処理
		void Initialize
		(
			ID3D11Device5*               pDevice,
			ID3D11DeviceContext4*        pContext,
			IDXGISwapChain4*             pSwapChain,
			const DirectX::CommonStates& commonStates
		);
		// 描画処理
		void Render();

		// フォントコレクションの作成
		void CreateFontCollection(const std::vector<std::wstring>& filePaths) { m_textRenderer.CreateFontCollection(filePaths); }
		// テキスト描画のリセット
		void ResetTextRenderer();
		// テキスト描画の初期化
		void InitializeTextRenderer(IDXGISwapChain4* pSwapChain);

		// 描画モードを返る
		void ChangeRenderMode();

		// モデル描画インタフェースを取得
		Renderings::IModel3DRenderer&  GetIModelRenderer()    { return m_modelRenderer; }
		// 画像描画インタフェースを取得
		Renderings::IImageRenderer&    GetIImageRenderer()    { return m_imageRenderer; }
		// テキスト描画インタフェースを取得
		Renderings::ITextRenderer&     GetITextRenderer()     { return m_textRenderer; }
		// 当たり判定描画インタフェースを取得
		Renderings::IColliderRenderer& GetIColliderRenderer() { return m_colliderRenderer; }


	private:


		/* 列挙型 */

		// 描画モード
		enum class RenderMode
		{
			Model,
			Both,
			Collider,
			Length
		};


		/* メンバ変数 */

		// モデル描画
		Renderings::Model3DRenderer  m_modelRenderer;
		// 画像描画
		Renderings::ImageRenderer    m_imageRenderer;
		// テキスト描画
		Renderings::TextRenderer     m_textRenderer;
		// 当たり判定描画
		Renderings::ColliderRenderer m_colliderRenderer;

		// 描画モード
		RenderMode m_renderMode;

	};
}
