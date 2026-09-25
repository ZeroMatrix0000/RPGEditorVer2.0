/*
 * FileName:     TextRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * テキスト描画
 */

#pragma once

#include "ITextRenderer.h"
#include "TextOutlineRenderer.h"

namespace Renderings
{
	class PixelShader;
	
	// テキスト描画
	class TextRenderer : public ITextRenderer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		TextRenderer();

		// 初期化処理
		void Initialize
		(
			ID3D11Device5*        pDevice,
			ID3D11DeviceContext4* pContext,
			IDXGISwapChain4*      pSwapChain,
			const PixelShader*    pOutlineShader
		);
		// フォントコレクションの作成
		void CreateFontCollection(const std::wstring& directoryPath);

		// 描画開始
		void Begin();
		// 描画処理
		void Draw(const Text* pText);
		// 描画終了
		void End();

		// リセット
		void Reset();

		// テキストのポインタを追加
		void AddPText(const Text* pText) override;
		// テキストのポインタを削除
		void RemovePText(const Text* pText) override;

		// テキストのポインタリストをソート
		void SortPTexts();

		// テキストのポインタリストを取得
		const std::vector<const Text*> GetPTexts() const { return m_pTexts; }


	private:


		/* メンバ変数 */

		// Direct2Dファクトリー
		Microsoft::WRL::ComPtr<ID2D1Factory8>   m_d2DFactory;
		// DirectWriteファクトリー
		Microsoft::WRL::ComPtr<IDWriteFactory8> m_dWriteFactory;

		// レンダーターゲット
		Microsoft::WRL::ComPtr<ID2D1RenderTarget> m_renderTarget;

		// フォントコレクション
		Microsoft::WRL::ComPtr<IDWriteFontCollection3> m_fontCollection;

		// 線のスタイル
		Microsoft::WRL::ComPtr<ID2D1StrokeStyle> m_strokeStyle;

		// テキストのポインタリスト
		std::vector<const Text*> m_pTexts;

		// デバイス
		ID3D11Device5* m_pDevice;
		// デバイスコンテキスト
		ID3D11DeviceContext4* m_pContext;

		// アウトラインシェーダ
		const Renderings::PixelShader* m_pOutlineShader;

	};
}
