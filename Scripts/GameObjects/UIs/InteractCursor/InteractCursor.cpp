/*
 * FileName:     InteractCursor.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/05
 *
 * 話しかける・調べる際のカーソル
 */

#include "Pch.h"
#include "InteractCursor.h"

#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/GameObjects/IGameObjectFinder.h"
#include "Scripts/Commons/Components/RectTransform.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Systems/JsonSerializer.h"

// コンストラクタ
InteractCursor::InteractCursor(const ComponentDesc& desc)
	: Component{ desc }
	, m_alpha{}
	, m_alphaVelocity{}
	, m_pTextTransform{}
	, m_pText{}
	, m_pImageTransform{}
	, m_pImage{}
{
}

// 初期化処理
void InteractCursor::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	m_alpha.Initialize(0.0f, 0.0f, 1.0f);

	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_alphaVelocity, "AlphaVelocity");
	serializer.Load(json);

	GameObject* pObj = Instantiate("Prefab_InteractCursorText");
	m_pTextTransform = pObj->GetComponent<RectTransform>();
	m_pText = pObj->GetComponent<Renderings::Text>();

	pObj = Instantiate("Prefab_InteractCursorImage");
	m_pImageTransform = pObj->GetComponent<RectTransform>();

	Renderings::Image* pImage = pObj->GetComponent<Renderings::Image>();
	m_pImage = pObj->GetComponent<Renderings::Image>();
}

// 更新処理
void InteractCursor::Update(float elapsedTime, bool isFocused)
{
	// 不透明度を設定
	m_alpha += m_alphaVelocity * elapsedTime * (isFocused ? 1.0f : -1.0f);

	Math::Color textColor = m_pText->GetFontColor();
	textColor.w = m_alpha;
	m_pText->SetFontColor(textColor);

	Math::Color imageColor = m_pImage->GetColor();
	imageColor.w = m_alpha;
	m_pImage->SetColor(imageColor);
}

// 名前を設定
void InteractCursor::SetName(const std::wstring& name)
{
	m_pText->SetStr(name);
}

// キャンバスを設定
void InteractCursor::SetCanvas(const Renderings::Canvas& canvas)
{
	m_pText->SetCanvas(canvas);
	m_pImage->SetCanvas(canvas);
}

// 座標を設定
void InteractCursor::SetPosition(const Math::Vector2& position)
{
	m_pTextTransform->SetPosition(position);
	m_pImageTransform->SetPosition(position);
}
