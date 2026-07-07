/*
 * FileName:     Renderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
 *
 * 描画
 */

#include "Pch.h"
#include "Renderer.h"

#include "Image.h"
#include "Text.h"

// コンストラクタ
Renderings::Renderer::Renderer(const Systems::IResources& iResources)
	: OnlyOne{ typeid(Renderer) }
	, m_modelRenderer{ iResources }
	, m_imageRenderer{ iResources }
	, m_textRenderer{}
{
}

// 初期化処理
void Renderings::Renderer::Initialize(ID3D11DeviceContext4* pContext, IDXGISwapChain4* pSwapChain, const DirectX::CommonStates& commonStates)
{
	// モデル描画の初期化
	m_modelRenderer.Initialize(pContext, commonStates);
	// 画像描画の初期化
	m_imageRenderer.Initialize(pContext, commonStates);
	// テキスト描画の初期化
	m_textRenderer.Initialize(pSwapChain);
}

// 描画処理
void Renderings::Renderer::Render()
{
	// モデルの描画
	m_modelRenderer.Render();

	// 画像のポインタリストをソート
	m_imageRenderer.SortPImages();
	// 画像のポインタリスト
	const auto& pImages = m_imageRenderer.GetPImages();

	// テキストのポインタリストをソート
	m_textRenderer.SortPTexts();
	// テキストのポインタリスト
	const auto& pTexts = m_textRenderer.GetPTexts();

	// 画像イテレータ
	auto itImage = pImages.begin();
	// テキストイテレータ
	auto itText = pTexts.begin();

	// テキストを描画したか
	bool wasDrawText = false;

	// 描画開始
	m_imageRenderer.Begin();
	m_textRenderer.Begin();

	// どちらも描画し切るまで
	while (itImage != pImages.end() || itText != pTexts.end())
	{
		// 画像を描画し終わったなら
		if (itImage == pImages.end())
		{
			wasDrawText = true;
			m_textRenderer.Draw(*itText);
			itText++;
			continue;
		}
		// テキストを描画し終わったなら
		if (itText == pTexts.end())
		{
			// 一度テキストを描画したならリセット
			if (wasDrawText)
			{
				wasDrawText = false;
				m_imageRenderer.End();
				m_textRenderer.End();
				m_imageRenderer.Begin();
				m_textRenderer.Begin();
			}

			m_imageRenderer.Draw(*itImage);
			itImage++;
			continue;
		}

		// 画像の描画
		if ((*itImage)->GetOrderInLayer() <= (*itText)->GetOrderInLayer())
		{
			// 一度テキストを描画したならリセット
			if (wasDrawText)
			{
				wasDrawText = false;
				m_imageRenderer.End();
				m_textRenderer.End();
				m_imageRenderer.Begin();
				m_textRenderer.Begin();
			}

			m_imageRenderer.Draw(*itImage);
			itImage++;
			continue;
		}
		// テキストの描画
		else
		{
			wasDrawText = true;
			m_textRenderer.Draw(*itText);
			itText++;
			continue;
		}
	}

	// 描画終了
	m_imageRenderer.End();
	m_textRenderer.End();
}

// テキスト描画のリセット
void Renderings::Renderer::ResetTextRenderer()
{
	m_textRenderer.Reset();
}

// テキスト描画の初期化
void Renderings::Renderer::InitializeTextRenderer(IDXGISwapChain4* pSwapChain)
{
	m_textRenderer.Initialize(pSwapChain);
}
