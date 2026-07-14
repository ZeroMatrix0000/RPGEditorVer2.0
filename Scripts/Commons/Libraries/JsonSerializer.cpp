/*
 * FileName:     JsonSerializer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * Jsonのシリアライズ
 */

#include "Pch.h"
#include "JsonSerializer.h"

// Json -> Vector2
Math::Vector2 Libraries::JsonSerializer::Json2Vector2(const nlohmann::ordered_json& json)
{
	return Math::Vector2
	{
		json.at("X").get<float>(),
		json.at("Y").get<float>()
	};
}
