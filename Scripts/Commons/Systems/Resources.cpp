/*
 * FileName:     Resources.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * リソース管理
 */

#include "Pch.h"
#include "Resources.h"

Systems::Resources::Resources()
	: IResources{}
	, m_models{}
{
}

// モデルを追加
void Systems::Resources::AddModel3D(const std::string& modelName, ID3D11Device* device, DirectX::EffectFactory* fx, const std::wstring& filePath)
{
	try
	{
		m_models.emplace(modelName, Renderings::Model3DSource::Create(device, fx, filePath));
	}
	catch (std::exception e)
	{
		// エラーメッセージを追加
		//GetInterface<IErrorMessage>().AddMessage(Utility::FormatWString
		//(
		//	L"モデルの読み込みに失敗しました。: %s",
		//	filePath.c_str()
		//));
	}
}

// モデルの取得
const Renderings::Model3DSource* Systems::Resources::GetModel3D(const std::string& modelName) const
{
	auto it = m_models.find(modelName);
	if (it == m_models.end())
	{
		return nullptr;
	}

	return &it->second;
}
