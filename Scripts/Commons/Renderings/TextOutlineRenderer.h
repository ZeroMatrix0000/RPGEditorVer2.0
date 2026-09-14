/*
 * FileName:     TextOutLineRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/14
 *
 * テキストのアウトライン描画
 */

#pragma once

namespace Renderings
{
	class Text;

	// テキストのアウトライン描画
	class TextOutlineRenderer : public IDWriteTextRenderer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		TextOutlineRenderer(float canvasRatio, ID2D1Factory* pFactory, ID2D1RenderTarget* pRenderTarget, const Text& text);

		// 描画
		HRESULT STDMETHODCALLTYPE DrawGlyphRun
		(
			void*                               clientDrawingContext,
			FLOAT                               baselineOriginX,
			FLOAT                               baselineOriginY,
			DWRITE_MEASURING_MODE               measuringMode,
			const DWRITE_GLYPH_RUN*             glyphRun,
			const DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
			IUnknown*                           clientDrawingEffect
		) override;

		HRESULT DrawInlineObject
		(
			void* clientDrawingContext,
			FLOAT                originX,
			FLOAT                originY,
			IDWriteInlineObject* inlineObject,
			BOOL                 isSideways,
			BOOL                 isRightToLeft,
			IUnknown*            clientDrawingEffect
		) override
		{
			return E_NOTIMPL;
		}

		HRESULT DrawStrikethrough
		(
			void*                       clientDrawingContext,
			FLOAT                       baselineOriginX,
			FLOAT                       baselineOriginY,
			DWRITE_STRIKETHROUGH const* strikethrough,
			IUnknown*                   clientDrawingEffect
		) override 
		{
			return E_NOTIMPL;
		}

		HRESULT DrawUnderline
		(
			void*                   clientDrawingContext,
			FLOAT                   baselineOriginX,
			FLOAT                   baselineOriginY,
			DWRITE_UNDERLINE const* underline,
			IUnknown*               clientDrawingEffect
		) override
		{
			return E_NOTIMPL;
		}

		// 現在の座標系を取得
		HRESULT GetCurrentTransform(void* clientDrawingContext, DWRITE_MATRIX* transform) override;

		// DPI を取得
		HRESULT GetPixelsPerDip(void* clientDrawingContext, FLOAT* pixelsPerDip) override;

		HRESULT QueryInterface(REFIID riid, void** ppvObject) override { return E_NOTIMPL; };

		ULONG AddRef() override { return 0; }
		ULONG Release() override { return 0; }

	private:


		/* メンバ関数 */

		// ピクセルスナップ設定
		HRESULT IsPixelSnappingDisabled
		(
			void* clientDrawingContext,
			BOOL* isDisabled
		) override;


		/* メンバ変数 */

		// キャンバスの表示倍率
		float m_canvasRatio;

		// ファクトリのポインタ
		ID2D1Factory* m_pFactory;

		// 描画ターゲットのポインタ
		ID2D1RenderTarget* m_pRenderTarget;

		// テキストのポインタ
		const Text& m_refText;

	};
}
