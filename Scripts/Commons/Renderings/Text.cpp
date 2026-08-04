/*
 * FileName:     Text.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
 *
 * テキスト
 */

#include "Pch.h"
#include "Text.h"

#include "ITextRenderer.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/IGameObjectFinder.h"
#include "../Renderings/Canvas.h"
#include "../Systems/JsonSerializer.h"

// コンストラクタ
Renderings::Text::Text(const ComponentDesc& desc, ITextRenderer* pITextRenderer)
	: Component{ desc }
	, m_str{ L"New Text" }
	, m_fontName{}
	, m_fontSize{}
	, m_fontColor{ D2D1::ColorF::White }
	, m_textAlignment{}
	, m_paragraphAlignment{}
	, m_orderInLayer{}
	, m_pCanvas{}
	, m_pITextRenderer{ pITextRenderer }
{
	// テキスト描画にポインタを追加
	m_pITextRenderer->AddPText(this);
}

// デストラクタ
Renderings::Text::~Text()
{
	// 画像描画からポインタを削除
	m_pITextRenderer->RemovePText(this);
}

// 初期化処理
void Renderings::Text::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	Math::Color fontColor = Math::Color{ m_fontColor.r, m_fontColor.g, m_fontColor.b, m_fontColor.a };

	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_str, "Str");
	serializer.AddParameter(&m_fontName, "FontName");
	serializer.AddParameter(&m_fontSize, "FontSize");
	serializer.AddParameter(&fontColor, "FontColor");
	serializer.AddParameter(&m_textAlignment, "TextAlignment");
	serializer.AddParameter(&m_paragraphAlignment, "ParagraphAlignment");
	serializer.AddParameter(&m_orderInLayer, "OrderInLayer");
	serializer.AddParameter(&m_pCanvas, "Canvas");
	serializer.Load(json);

	SetFontColor(fontColor);
}
