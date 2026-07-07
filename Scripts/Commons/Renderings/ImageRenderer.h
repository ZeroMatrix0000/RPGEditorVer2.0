/*
 * FileName:     ImageRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
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
		void Initialize(ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates);
		// 描画処理
		void Render();

		// 画像のポインタを追加
		void AddPImage(const Image* pImage) override;
		// 画像のポインタを削除
		void RemovePImage(const Image* pImage) override;

		// 画像の大きさを取得
		Math::Vector2 GetImageSize(const Image* pImage) const override;


	private:


		/* メンバ変数 */

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		// 画像のポインタリスト
		std::vector<const Image*> m_pImages;

		// コモンステート
		const DirectX::CommonStates* m_pCommonStates;

		// リソースのインタフェースの参照
		const Systems::IResources& m_refIResources;

	};
}
