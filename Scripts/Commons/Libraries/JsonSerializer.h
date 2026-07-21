/*
 * FileName:     JsonSerializer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
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
		// Json -> Vector3
		Math::Vector3 Json2Vector3(const nlohmann::ordered_json& json);
		// Json -> Euler
		Math::Euler Json2Euler(const nlohmann::ordered_json& json);

		// Json -> Camera
		template<typename TCamera> requires IsSame
		<
			TCamera,
			Camera::QuaternionCamera,
			Camera::QuaternionTargetCamera,
			Camera::EulerCamera,
			Camera::EulerTargetCamera
		>
		inline TCamera Json2Camera(const nlohmann::ordered_json& json) { return TCamera{}; }
		// Json -> QuaternionCamera
		template<>
		inline Camera::QuaternionCamera Json2Camera(const nlohmann::ordered_json& json)
		{
			return Camera::QuaternionCamera
			{
				Json2Vector3(json.at("Position")),
				Json2Euler(json.at("Rotation")).CreateQuaternion()
			};
		}
		// Json -> QuaternionTargetCamera
		template<>
		inline Camera::QuaternionTargetCamera Json2Camera(const nlohmann::ordered_json& json)
		{
			return Camera::QuaternionTargetCamera
			{
				Json2Vector3(json.at("Position")),
				Json2Euler(json.at("Rotation")).CreateQuaternion(),
				json.at("Distance").get<float>()
			};
		}
		// Json -> EulerCamera
		template<>
		inline Camera::EulerCamera Json2Camera(const nlohmann::ordered_json& json)
		{
			return Camera::EulerCamera
			{
				Json2Vector3(json.at("Position")),
				Json2Euler(json.at("Rotation"))
			};
		}
		// Json -> EulerTargetCamera
		template<>
		inline Camera::EulerTargetCamera Json2Camera(const nlohmann::ordered_json& json)
		{
			return Camera::EulerTargetCamera
			{
				Json2Vector3(json.at("Position")),
				Json2Euler(json.at("Rotation")),
				json.at("Distance").get<float>()
			};
		}
	}
}
