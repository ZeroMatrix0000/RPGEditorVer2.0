/*
 * FileName:     IModel3DRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 3Dモデル描画のインタフェース
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace Renderings
{
	class ICameraScreen;

	// 3Dモデル描画のインタフェース
	class IModel3DRenderer : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		IModel3DRenderer()
			: OnlyOne{ typeid(IModel3DRenderer) }
		{
		}
		// デストラクタ
		virtual ~IModel3DRenderer() = default;

		// カメラ画面インタフェースのポインタを追加
		virtual void AddPICameraScreen(const ICameraScreen* pICameraScreen) = 0;
		// カメラ画面インタフェースのポインタを削除
		virtual void RemovePICameraScreen(const ICameraScreen* pICameraScreen) = 0;

	};
}
