/*
 * FileName:     TextRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * テキスト描画
 */

#pragma once

#include "ITextRenderer.h"

namespace Renderings
{
	// テキスト描画
	class TextRenderer : public ITextRenderer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		TextRenderer();

		// 初期化処理
		void Initialize(IDXGISwapChain4* pSwapChain);
		// フォントコレクションの作成
		void CreateFontCollection(const std::vector<std::wstring>& filePaths);

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

		// テキストのポインタリスト
		std::vector<const Text*> m_pTexts;

	};
}
