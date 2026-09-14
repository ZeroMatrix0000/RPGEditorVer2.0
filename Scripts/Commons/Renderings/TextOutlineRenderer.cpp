/*
 * FileName:     TextOutLineRenderer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/14
 *
 * テキストのアウトライン描画
 */

#include "Pch.h"
#include "TextOutlineRenderer.h"
#include "Text.h"
#include "../Components/RectTransform.h"

// コンストラクタ
Renderings::TextOutlineRenderer::TextOutlineRenderer(float canvasRatio, ID2D1Factory* pFactory, ID2D1RenderTarget* pRenderTarget, const Text& text)
	: m_canvasRatio{ canvasRatio }
	, m_pFactory{ pFactory }
	, m_pRenderTarget{ pRenderTarget }
	, m_refText{ text }
{
}

// 描画
HRESULT __stdcall Renderings::TextOutlineRenderer::DrawGlyphRun(void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, const DWRITE_GLYPH_RUN* glyphRun, const DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription, IUnknown* clientDrawingEffect)
{
	// 曲線データ
	Microsoft::WRL::ComPtr<ID2D1PathGeometry> geometry;
	HRESULT hr = m_pFactory->CreatePathGeometry(geometry.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	// 曲線
	Microsoft::WRL::ComPtr<ID2D1GeometrySink> sink;
	hr = geometry->Open(sink.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	// アウトライン曲線を取得
	hr = glyphRun->fontFace->GetGlyphRunOutline
	(
		glyphRun->fontEmSize,
		glyphRun->glyphIndices,
		glyphRun->glyphAdvances,
		glyphRun->glyphOffsets,
		glyphRun->glyphCount,
		glyphRun->isSideways,
		glyphRun->bidiLevel & 1,
		sink.Get()
	);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = sink->Close();
	if (FAILED(hr))
	{
		return hr;
	}

	// 座標系を適用させた図形
	Microsoft::WRL::ComPtr<ID2D1TransformedGeometry> transformed;
	hr = m_pFactory->CreateTransformedGeometry(
		geometry.Get(),
		D2D1::Matrix3x2F::Translation(
			baselineOriginX,
			baselineOriginY
		),
		transformed.GetAddressOf()
	);
	if (FAILED(hr))
	{
		return hr;
	}

	// アウトラインの描画
	if (m_refText.GetOutlineWidth() != 0.0f)
	{
		// アウトラインブラシ
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineBrush;
		hr = m_pRenderTarget->CreateSolidColorBrush
		(
			m_refText.GetD2D1OutlineColor(),
			outlineBrush.GetAddressOf()
		);
		if (FAILED(hr))
		{
			return hr;
		}

		// 線のスタイルの詳細（角を丸める）
		D2D1_STROKE_STYLE_PROPERTIES props{};
		props.lineJoin = D2D1_LINE_JOIN_ROUND;
		
		// 線のスタイル
		Microsoft::WRL::ComPtr<ID2D1StrokeStyle> strokeStyle;
		m_pFactory->CreateStrokeStyle(
			props,
			nullptr,
			0,
			strokeStyle.GetAddressOf()
		);

		m_pRenderTarget->DrawGeometry(transformed.Get(), outlineBrush.Get(), m_refText.GetOutlineWidth()* m_canvasRatio, strokeStyle.Get());
	}

	// テキストブラシ
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> textBrush;
	hr = m_pRenderTarget->CreateSolidColorBrush
	(
		m_refText.GetD2D1FontColor(),
		textBrush.GetAddressOf()
	);
	if (FAILED(hr))
	{
		return hr;
	}

	m_pRenderTarget->FillGeometry(transformed.Get(), textBrush.Get());

	return S_OK;
}

// 現在の座標系を取得
HRESULT Renderings::TextOutlineRenderer::GetCurrentTransform(void* clientDrawingContext, DWRITE_MATRIX* transform)
{
	if (!transform)
	{
		return E_INVALIDARG;
	}

	transform->m11 = 1.0f;
	transform->m12 = 0.0f;
	transform->m21 = 0.0f;
	transform->m22 = 1.0f;
	transform->dx = 0.0f;
	transform->dy = 0.0f;

	return S_OK;
}

// DPI を取得
HRESULT Renderings::TextOutlineRenderer::GetPixelsPerDip(void* clientDrawingContext, FLOAT* pixelsPerDip)
{
	if (!pixelsPerDip)
	{
		return E_INVALIDARG;
	}

	*pixelsPerDip = 1.0f;
	return S_OK;
}

// ピクセルスナップ設定
HRESULT Renderings::TextOutlineRenderer::IsPixelSnappingDisabled(void* clientDrawingContext, BOOL* isDisabled)
{
	if (!isDisabled)
	{
		return E_INVALIDARG;
	}

	*isDisabled = true;
	return S_OK;
}
