/*
 * FileName:     JsonSerializer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
 *
 * Jsonのシリアライズ
 */

#include "Pch.h"
#include "JsonSerializer.h"

#include "../Systems/IErrorMessage.h"

std::unordered_map<std::type_index, std::function<void(void*, const nlohmann::ordered_json&, IGameObjectFinder*)>> Systems::JsonSerializer::s_methods{};

// コンストラクタ
Systems::JsonSerializer::JsonSerializer(IGameObjectFinder* pIGameObjectFinder)
	: m_parameters{}
	, m_pIGameObjectFinder{ pIGameObjectFinder }
{
}

// パラメータを読み込む
void Systems::JsonSerializer::Load(const nlohmann::ordered_json& json)
{
	if (!m_pIGameObjectFinder)
	{
		// エラーメッセージを追加
		IErrorMessage::GetInstance()->AddMessage(L"ゲームオブジェクトを探すことが出来ません。");
		return;
	}

	for (const auto& element : json.items())
	{
		// パラメータ名
		const std::string& name = element.key();
		
		// パラメータを探す
		auto it = m_parameters.find(name);
		// パラメータが見つからなかったら
		if (it == m_parameters.end())
		{
			// エラーメッセージを追加
			IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
			(
				L"パラメータが見つかりません。 | name: %s",
				Utility::string2wstring(name.c_str()).c_str()
			));
			continue;
		}

		try
		{
			s_methods.at(it->second.index)(it->second.ptr, element.value(), m_pIGameObjectFinder);
		}
		catch (std::exception e)
		{
			// エラーメッセージを追加
			IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
			(
				L"パラメータの読み込みに失敗しました。 | name: %s",
				Utility::string2wstring(name.c_str()).c_str()
			));
			continue;
		}
	}
}
