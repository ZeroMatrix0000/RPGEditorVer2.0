/*
 * FileName:     Resources.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * リソース管理
 */

#pragma once

#include "IResources.h"

namespace Systems
{
	class Resources : public IResources
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Resources();

		// モデルを追加
		void AddModelSource(const std::string& modelSourceName, ID3D11Device* device, DirectX::EffectFactory* fx, const std::wstring& filePath);

		// モデルの取得
		const Renderings::Model3DSource* GetModelSource(const std::string& modelName) const override;


	private:


		/* メンバ変数 */

		// モデルソースリスト
		std::unordered_map<std::string, Renderings::Model3DSource> m_modelSources;

	};
}
