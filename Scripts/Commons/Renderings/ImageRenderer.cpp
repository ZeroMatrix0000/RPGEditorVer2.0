/*
 * FileName:     ImageRenderer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
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
		const ImageSource* pImageSource = m_refIResources.GetImageSource(pImage->GetImageSourceName());
		if (!pImageSource)
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

		// テクスチャの詳細
		D3D11_TEXTURE2D_DESC textureDesc;
		pImageSource->GetResource()->GetDesc(&textureDesc);

		// テクスチャの中心
		Math::Vector2 origin = Math::Vector2
		{
			static_cast<float>(textureDesc.Width),
			static_cast<float>(textureDesc.Height)
		};

		// ピボットにあわせて画像の中心を移動
		switch (pRectTransform->GetPivot())
		{
		case Utility::AlignmentPoint::TopLeft:
			origin.x = 0.0f;
			origin.y = 0.0f;
			break;
		case Utility::AlignmentPoint::TopCenter:
			origin.x /= 2.0f;
			origin.y = 0.0f;
			break;
		case Utility::AlignmentPoint::TopRight:
			origin.y = 0.0f;
			break;
		case Utility::AlignmentPoint::MiddleLeft:
			origin.x = 0.0f;
			origin.y /= 2.0f;
			break;
		case Utility::AlignmentPoint::MiddleCenter:
			origin.x /= 2.0f;
			origin.y /= 2.0f;
			break;
		case Utility::AlignmentPoint::MiddleRight:
			origin.y /= 2.0f;
			break;
		case Utility::AlignmentPoint::BottomLeft:
			origin.x = 0.0f;
			break;
		case Utility::AlignmentPoint::BottomCenter:
			origin.x /= 2.0f;
			break;
		default:
			break;
		}

		// 長方形
		Math::Rect rect = pRectTransform->GetRect();
		// キャンバスサイズ
		Math::Vector2 canvasSize = pCanvas->GetSize();

		// アンカーに合わせて画像を移動
		switch (pRectTransform->GetAnchor())
		{
		case Utility::AlignmentPoint::TopCenter:
			rect.position.x += canvasSize.x / 2.0f;
			break;
		case Utility::AlignmentPoint::TopRight:
			rect.position.x += canvasSize.x;
			break;
		case Utility::AlignmentPoint::MiddleLeft:
			rect.position.y += canvasSize.y / 2.0f;
			break;
		case Utility::AlignmentPoint::MiddleCenter:
			rect.position.x += canvasSize.x / 2.0f;
			rect.position.y += canvasSize.y / 2.0f;
			break;
		case Utility::AlignmentPoint::MiddleRight:
			rect.position.x += canvasSize.x;
			rect.position.y += canvasSize.y / 2.0f;
			break;
		case Utility::AlignmentPoint::BottomLeft:
			rect.position.y += canvasSize.y;
			break;
		case Utility::AlignmentPoint::BottomCenter:
			rect.position.x += canvasSize.x / 2.0f;
			rect.position.y += canvasSize.y;
			break;
		case Utility::AlignmentPoint::BottomRight:
			rect.position.x += canvasSize.x;
			rect.position.y += canvasSize.y;
			break;
		default:
			break;
		}

		// キャンバスの表示倍率
		float canvasRatio = pCanvas->GetRatio();
		// 表示倍率を適用
		rect.position *= canvasRatio;
		rect.size     *= canvasRatio;

		// 描画 TODO
		m_spriteBatch->Draw
		(
			pImageSource->GetTexture(),
			RECT
			{
				Math::RoundInt(rect.position.x),
				Math::RoundInt(rect.position.y),
				Math::RoundInt(rect.position.x + rect.size.x),
				Math::RoundInt(rect.position.y + rect.size.y),
			},
			nullptr,
			pImage->GetColor(),
			Math::Deg2Rad(pRectTransform->GetAngle()),
			origin
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

// 画像の大きさを取得
Math::Vector2 Renderings::ImageRenderer::GetImageSize(const Image* pImage) const
{
	// 画像ソース
	const ImageSource* pImageSource = m_refIResources.GetImageSource(pImage->GetImageSourceName());
	if (!pImageSource)
	{
		return Math::Vector2::Zero;
	}

	// テクスチャの詳細
	D3D11_TEXTURE2D_DESC textureDesc;
	pImageSource->GetResource()->GetDesc(&textureDesc);

	return Math::Vector2
	{
		static_cast<float>(textureDesc.Width),
		static_cast<float>(textureDesc.Height)
	};
}
