/*
 * FileName:     JsonSerializer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * Jsonのシリアライズ
 */

#include "Pch.h"
#include "JsonSerializer.h"

 // Json -> Color
Math::Color Libraries::JsonSerializer::Json2Color(const nlohmann::ordered_json& json)
{
	return Math::Color
	{
		json.at("R").get<float>(),
		json.at("G").get<float>(),
		json.at("B").get<float>(),
		json.at("A").get<float>()
	};
}

// Json -> Vector2
Math::Vector2 Libraries::JsonSerializer::Json2Vector2(const nlohmann::ordered_json& json)
{
	return Math::Vector2
	{
		json.at("X").get<float>(),
		json.at("Y").get<float>()
	};
}
