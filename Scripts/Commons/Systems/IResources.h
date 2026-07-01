/*
 * FileName:     IResources.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * リソースのインタフェース
 */

#pragma once

#include "OnlyOne.h"
#include "../Renderings/Model3DSource.h"

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
		virtual const Renderings::Model3DSource* GetModel3D(const std::string& modelName) const = 0;

	};
}
