/*
 * FileName:     Image.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 画像
 */

#pragma once

#include "../GameObjects/Component.h"

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
		Image(const ComponentCreatePermit& permit, GameObject* pOwner, IImageRenderer* pIImageRenderer);
		// デストラクタ
		~Image();

		// 画像ソース名を設定
		void SetImageSourceName(const std::string& imageSourceName) { m_imageSourceName = imageSourceName; }

		// キャンバスを設定
		void SetCanvas(const Canvas& canvas) { m_pCanvas = &canvas; }

		// 画像ソース名を取得
		const std::string& GetImageSourceName() const { return m_imageSourceName; }

		// レイヤー順を取得
		int GetOrderInLayer() const { return m_orderInLayer; }

		// キャンバスのポインタを取得
		const Canvas* GetPCanvas() const { return m_pCanvas; }


	private:


		/* メンバ変数 */

		// 画像ソース名
		std::string m_imageSourceName;

		// レイヤー順
		int m_orderInLayer;

		// キャンバスのポインタ
		const Canvas* m_pCanvas;

		// 画像インタフェースのポインタ
		IImageRenderer* m_pIImageRenderer;

	};
}
