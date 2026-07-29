/*
 * FileName:     Resources.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/29
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
		// メッシュを読み込む
		void LoadMeshes(const std::wstring& directoryPath);
		// ピクセルシェーダを読み込む
		void LoadPixelShaders(ID3D11Device* device, const std::wstring& directoryPath);

		// モデルの取得
		const Renderings::Model3DSource* GetModelSource(const std::string& modelName)  const override;
		// 画像の取得
		const Renderings::ImageSource*   GetImageSource(const std::string& imageName)  const override;
		// Jsonの取得
		const nlohmann::ordered_json*    GetJson(const std::string& jsonName)          const override;
		// Jsonの取得
		const Mesh*                      GetMesh(const std::string& meshName)          const override;
		// ピクセルシェーダの取得
		ID3D11PixelShader*               GetPixelShader(const std::string& shaderName) const override;


	private:

		/* メンバ関数 */


		/* メンバ変数 */

		// モデルソースリスト
		std::unordered_map<std::string, Renderings::Model3DSource> m_modelSources;
		// 画像ソースリスト
		std::unordered_map<std::string, Renderings::ImageSource> m_imageSources;
		// Jsonリスト
		std::unordered_map<std::string, nlohmann::ordered_json> m_jsons;
		// メッシュリスト
		std::unordered_map<std::string, Mesh> m_meshes;
		// ピクセルシェーダリスト
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> m_pixelShaders;

	};
}
