/*
 * FileName:     Resources.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * リソース管理
 */

#include "Pch.h"
#include "Resources.h"

#include "IErrorMessage.h"

Systems::Resources::Resources()
	: IResources{}
	, m_modelSources{}
	, m_imageSources{}
{
}

// モデルを追加
void Systems::Resources::LoadModelSource(ID3D11Device* device, DirectX::EffectFactory* fx, const std::string& directoryPath)
{
	// ディレクトリ内を全て検索
	for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath))
	{
		// ファイルなら
		if (entry.is_regular_file())
		{
			try
			{
				m_modelSources.emplace(entry.path().stem().string(), Renderings::Model3DSource::Create(device, fx, entry.path().wstring()));
			}
			catch (std::exception e)
			{
				// エラーメッセージを追加
				IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
				(
					L"モデルの読み込みに失敗しました。: %s",
					entry.path().c_str()
				));
			}
		}
	}
}

// 画像を読み込む
void Systems::Resources::LoadImageSource(ID3D11Device5* device, const std::string& directoryPath)
{
	// ディレクトリ内を全て検索
	for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath))
	{
		// ファイルなら
		if (entry.is_regular_file())
		{
			try
			{
				m_imageSources.emplace(entry.path().stem().string(), Renderings::ImageSource::Create(device, entry.path().wstring()));
			}
			catch (std::exception e)
			{
				// エラーメッセージを追加
				IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
				(
					L"画像の読み込みに失敗しました。: %s",
					entry.path().c_str()
				));
			}
		}
	}
}

// モデルの取得
const Renderings::Model3DSource* Systems::Resources::GetModelSource(const std::string& modelName) const
{
	auto it = m_modelSources.find(modelName);
	if (it == m_modelSources.end())
	{
		return nullptr;
	}

	return &it->second;
}

// 画像の取得
const Renderings::ImageSource* Systems::Resources::GetImageSource(const std::string& imageName) const
{
	auto it = m_imageSources.find(imageName);
	if (it == m_imageSources.end())
	{
		return nullptr;
	}

	return &it->second;
}
