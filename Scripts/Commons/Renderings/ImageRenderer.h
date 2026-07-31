/*
 * FileName:     ImageRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/31
 *
 * 画像描画
 */

#pragma once

#include "IImageRenderer.h"

namespace Systems
{
	class IResources;
}

namespace Renderings
{
	// 画像描画
	class ImageRenderer : public IImageRenderer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ImageRenderer(const Systems::IResources& iResources);

		// 初期化処理
		void Initialize(ID3D11Device5* pDevice, ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates);
		// 更新処理
		void Update(float elapsedTime);

		// 描画開始
		void Begin();
		// 描画処理
		void Draw(const Image* pImage);
		// 描画終了
		void End();

		// 画像のポインタを追加
		void AddPImage(const Image* pImage) override;
		// 画像のポインタを削除
		void RemovePImage(const Image* pImage) override;

		// 画像の大きさを取得
		Math::Vector2 GetImageSize(const Image* pImage) const override;

		// 画像のポインタリストのソート
		void SortPImages();

		// 画像のポインタリストを取得
		const std::vector<const Image*> GetPImages() const { return m_pImages; }


	private:


		/* 構造体 */

		// シェーダの定数バッファの詳細
		struct ConstBufferDesc
		{
			// テクスチャサイズ
			Math::Vector2 textureSize{};
			// 実行時間
			float time{};
			// 余白
			float unusedSpace{};
		};


		/* メンバ変数 */

		// 定数バッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_constBuffer;
		// 定数バッファの詳細
		ConstBufferDesc m_constBufferDesc;

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		// 画像のポインタリスト
		std::vector<const Image*> m_pImages;

		// デバイスコンテキスト
		ID3D11DeviceContext4* m_pContext;

		// コモンステート
		const DirectX::CommonStates* m_pCommonStates;

		// リソースのインタフェースの参照
		const Systems::IResources& m_refIResources;

	};
}
