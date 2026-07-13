/*
 * FileName:     Resources.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
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
		void LoadModelSources(ID3D11Device* device, DirectX::EffectFactory* fx, const std::wstring& directoryPath);
		// 画像を読み込む
		void LoadImageSources(ID3D11Device5* device, const std::wstring& directoryPath);
		// Jsonを読み込む
		void LoadJsons(const std::wstring& directoryPath);

		// モデルの取得
		const Renderings::Model3DSource* GetModelSource(const std::string& modelName) const override;
		// 画像の取得
		const Renderings::ImageSource*   GetImageSource(const std::string& imageName) const override;
		// Jsonの取得
		const nlohmann::ordered_json*    GetJson(const std::string& jsonName)         const override;


	private:

		/* メンバ関数 */


		/* メンバ変数 */

		// モデルソースリスト
		std::unordered_map<std::string, Renderings::Model3DSource> m_modelSources;
		// 画像ソースリスト
		std::unordered_map<std::string, Renderings::ImageSource> m_imageSources;
		// Jsonリスト
		std::unordered_map<std::string, nlohmann::ordered_json> m_jsons;

	};
}
