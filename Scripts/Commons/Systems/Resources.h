/*
 * FileName:     Resources.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * リソース管理
 */

#pragma once

#include "IResources.h"

namespace Systems
{
	// リソース管理
	class Resources : public IResources
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Resources();

		// モデルを読み込む
		void LoadModelSource(ID3D11Device* device, DirectX::EffectFactory* fx, const std::string& directoryPath);
		// 画像を読み込む
		void LoadImageSource(ID3D11Device5* device, const std::string& directoryPath);

		// モデルの取得
		const Renderings::Model3DSource* GetModelSource(const std::string& modelName) const override;
		// 画像の取得
		const Renderings::ImageSource* GetImageSource(const std::string& imageName)   const override;


	private:

		/* メンバ関数 */


		/* メンバ変数 */

		// モデルソースリスト
		std::unordered_map<std::string, Renderings::Model3DSource> m_modelSources;
		// 画像ソースリスト
		std::unordered_map<std::string, Renderings::ImageSource> m_imageSources;

	};
}
