/*
 * FileName:     RectTransform.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * 2D用トランスフォーム
 */

#include "Pch.h"
#include "RectTransform.h"

// コンストラクタ
Components::RectTransform::RectTransform(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Component{ permit, pOwner }
	, m_rect{}
	, m_angle{}
	, m_pivot{ Utility::AlignmentPoint::MiddleCenter }
	, m_anchor{ Utility::AlignmentPoint::MiddleCenter }
{
}

// 初期化処理
void Components::RectTransform::Initalize(const nlohmann::ordered_json& json)
{
	// 要素ごとにループ
	for (const auto& element : json.items())
	{
		const std::string& key = element.key();
		if (key == "Position")
		{
			SetPosition(JsonSerializer::Json2Vector2(element.value()));
		}
		else if (key == "Size")
		{
			SetSize(JsonSerializer::Json2Vector2(element.value()));
		}
		else if (key == "Angle")
		{
			SetAngle(element.value().get<float>());
		}
		else if (key == "Pivot")
		{
			SetPivot(JsonSerializer::Json2Enum<Utility::AlignmentPoint>(element.value()));
		}
		else if (key == "Anchor")
		{
			SetAnchor(JsonSerializer::Json2Enum<Utility::AlignmentPoint>(element.value()));
		}
		else
		{
			Utility::Throw();
		}
	}
}
