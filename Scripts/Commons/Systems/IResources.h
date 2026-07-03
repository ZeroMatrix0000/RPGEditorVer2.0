/*
 * FileName:     IResources.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * リソースのインタフェース
 */

#pragma once

#include "OnlyOne.h"
#include "../Renderings/Model3DSource.h"
#include "../Renderings/ImageSource.h"

namespace Systems
{
	class IResources : public OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		IResources()
			: OnlyOne{ typeid(IResources) }
		{
		}
		// デストラクタ
		virtual ~IResources() = default;

		// モデルの取得
		virtual const Renderings::Model3DSource* GetModelSource(const std::string& modelName) const = 0;
		// 画像の取得
		virtual const Renderings::ImageSource* GetImageSource(const std::string& imageName)   const = 0;

	};
}
