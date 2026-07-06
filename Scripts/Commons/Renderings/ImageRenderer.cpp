/*
 * FileName:     ImageRenderer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 画像描画
 */

#include "Pch.h"
#include "ImageRenderer.h"

#include "ImageSource.h"
#include "Image.h"
#include "Canvas.h"
#include "../Systems/IResources.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/RectTransform.h"

// コンストラクタ
Renderings::ImageRenderer::ImageRenderer(const Systems::IResources& iResources)
	: IImageRenderer{}
	, m_spriteBatch{}
	, m_pImages{}
	, m_pCommonStates{}
	, m_refIResources{ iResources }
{
}

// 初期化処理
void Renderings::ImageRenderer::Initialize(ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates)
{
	m_pCommonStates = &commonStates;
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(pContext);
}

// 描画処理
void Renderings::ImageRenderer::Render()
{
	// 描画開始
	m_spriteBatch->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		m_pCommonStates->NonPremultiplied()
	);

	// レイヤー順にソート
	std::ranges::sort(m_pImages, [](const Image* p1, const Image* p2) {return p1->GetOrderInLayer() < p2->GetOrderInLayer(); });

	for (const auto* pImage : m_pImages)
	{
		// 画像ソース
		const ImageSource* imageSource = m_refIResources.GetImageSource(pImage->GetImageSourceName());
		if (!imageSource)
		{
			return;
		}

		// モデルの所有者の2Dトランスフォーム
		const RectTransform* pRectTransform = pImage->GetPOwner()->GetConstComponent<RectTransform>();
		if (!pRectTransform)
		{
			return;
		}

		// モデルが映るキャンバス
		const Canvas* pCanvas = pImage->GetPCanvas();
		if (!pCanvas)
		{
			return;
		}

		// テクスチャの設定
		D3D11_TEXTURE2D_DESC textureDesc;
		imageSource->GetResource()->GetDesc(&textureDesc);

		// 描画 TODO
		m_spriteBatch->Draw
		(
			imageSource->GetTexture(),
			Math::Vector2::Zero
		);
	}

	// 描画終了
	m_spriteBatch->End();
}

// 画像のポインタを追加
void Renderings::ImageRenderer::AddPImage(const Image* pImage)
{
	m_pImages.push_back(pImage);
}

// 画像のポインタを削除
void Renderings::ImageRenderer::RemovePImage(const Image* pImage)
{
	auto it = std::ranges::find(m_pImages, pImage);
	if (it != m_pImages.end())
	{
		m_pImages.erase(it);
	}
}
