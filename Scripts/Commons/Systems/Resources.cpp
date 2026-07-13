/*
 * FileName:     Resources.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
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
void Systems::Resources::LoadModelSources(ID3D11Device* device, DirectX::EffectFactory* fx, const std::wstring& directoryPath)
{
	// パスが存在しないなら
	if (!std::filesystem::exists(directoryPath))
	{
		// エラーメッセージを追加
		IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
		(
			L"パスが間違っています。: %s",
			directoryPath.c_str()
		));
		return;
	}
	
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
void Systems::Resources::LoadImageSources(ID3D11Device5* device, const std::wstring& directoryPath)
{
	// パスが存在しないなら
	if (!std::filesystem::exists(directoryPath))
	{
		// エラーメッセージを追加
		IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
		(
			L"パスが間違っています。: %s",
			directoryPath.c_str()
		));
		return;
	}

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

// Jsonを読み込む
void Systems::Resources::LoadJsons(const std::wstring& directoryPath)
{
	// パスが存在しないなら
	if (!std::filesystem::exists(directoryPath))
	{
		// エラーメッセージを追加
		IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
		(
			L"パスが間違っています。: %s",
			directoryPath.c_str()
		));
		return;
	}

	// ディレクトリ内を全て検索
	for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath))
	{
		// ファイルなら
		if (entry.is_regular_file())
		{
			std::ifstream fileStream{ entry.path() };
			// 開けなかったら終了
			if (!fileStream.is_open())
			{
				// エラーメッセージの追加
				Systems::IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
				(
					L"JSONファイルを開くことが出来ませんでした。: %s",
					entry.path().c_str()
				));
				fileStream.close();
				continue;
			}

			try
			{
				m_jsons.emplace(entry.path().stem().string(), nlohmann::ordered_json::parse(fileStream));
			}
			catch (std::exception e)
			{
				// エラーメッセージを追加
				IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
				(
					L"JSONファイルのフォーマットが正しくありません。: %s",
					entry.path().c_str()
				));
			}
			fileStream.close();
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

// Jsonの取得
const nlohmann::ordered_json* Systems::Resources::GetJson(const std::string& jsonName) const
{
	auto it = m_jsons.find(jsonName);
	if (it == m_jsons.end())
	{
		return nullptr;
	}

	return &it->second;
}
