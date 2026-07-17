/*
 * FileName:     Image.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/17
 *
 * 画像
 */

#pragma once

#include "../Components/Component.h"

namespace Renderings
{
	class Canvas;
	class IImageRenderer;

	// 画像
	class Image : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Image(const ComponentDesc& desc, IImageRenderer* pIImageRenderer);
		// デストラクタ
		~Image();

		// 初期化処理
		void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

		// 画像ソース名を設定
		void SetImageSourceName(const std::string& imageSourceName) { m_imageSourceName = imageSourceName; }
		// 色を設定
		void SetColor(const Math::Color& color) { m_color = color; }
		// 色を設定
		void SetColor(const DirectX::XMVECTORF32& color) { m_color = color; }

		// レイヤー順を設定
		void SetOrderInLayer(int orderInLayer) { m_orderInLayer = orderInLayer; }

		// キャンバスを設定
		void SetCanvas(const Canvas& canvas) { m_pCanvas = &canvas; }

		// 画像ソース名を取得
		const std::string& GetImageSourceName() const { return m_imageSourceName; }
		// 色を取得
		const Math::Color& GetColor() const { return m_color; }

		// レイヤー順を取得
		int GetOrderInLayer() const { return m_orderInLayer; }

		// キャンバスのポインタを取得
		const Canvas* GetPCanvas() const { return m_pCanvas; }

		// 画像サイズを取得
		Math::Vector2 GetSize() const;


	private:


		/* メンバ変数 */

		// 画像ソース名
		std::string m_imageSourceName;
		// 色
		Math::Color m_color;

		// レイヤー順
		int m_orderInLayer;

		// キャンバスのポインタ
		const Canvas* m_pCanvas;

		// 画像描画インタフェースのポインタ
		IImageRenderer* m_pIImageRenderer;

	};
}
