/*
 * FileName:     JsonSerializer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
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

// Json -> Vector3
Math::Vector3 Libraries::JsonSerializer::Json2Vector3(const nlohmann::ordered_json& json)
{
	return Math::Vector3
	{
		json.at("X").get<float>(),
		json.at("Y").get<float>(),
		json.at("Z").get<float>()
	};
}

// Json -> Euler
Math::Euler Libraries::JsonSerializer::Json2Euler(const nlohmann::ordered_json& json)
{
	return Math::Euler
	{
		json.at("X").get<float>(),
		json.at("Y").get<float>(),
		json.at("Z").get<float>()
	};
}
