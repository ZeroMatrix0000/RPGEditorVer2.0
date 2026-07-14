/*
 * FileName:     JsonSerializer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * Jsonのシリアライズ
 */

#pragma once

namespace Libraries
{
	// Jsonのシリアライズ
	namespace JsonSerializer
	{
		// Json -> 列挙型
		template<typename TEnum> requires std::is_enum_v<TEnum>
		inline TEnum Json2Enum(const nlohmann::ordered_json& json)
		{
			return magic_enum::enum_cast<TEnum>(json.get<std::string>()).value();
		}

		// Json -> Color
		Math::Color Json2Color(const nlohmann::ordered_json& json);
		// Json -> Vector2
		Math::Vector2 Json2Vector2(const nlohmann::ordered_json& json);
	}
}
