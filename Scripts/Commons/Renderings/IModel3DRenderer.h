/*
 * FileName:     IModel3DRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/02
 *
 * 3Dモデル描画のインタフェース
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace Renderings
{
	// 前方宣言
	class Model3D;

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

		// モデルのポインタを追加
		virtual void AddModel(const Model3D* pModel) = 0;
		// モデルのポインタを削除
		virtual void RemoveModel(const Model3D* pModel) = 0;

	};
}
