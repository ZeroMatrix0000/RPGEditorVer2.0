/*
 * FileName:     Text.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
 *
 * テキスト
 */

#include "Pch.h"
#include "Text.h"

#include "ITextRenderer.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/IGameObjectFinder.h"
#include "../Renderings/Canvas.h"

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
	// 要素ごとにループ
	for (const auto& element : json.items())
	{
		const std::string& key = element.key();
		if (key == "Str")
		{
			SetStr(Utility::string2wstring(element.value().get<std::string>()));
		}
		else if (key == "FontName")
		{
			SetFontName(Utility::string2wstring(element.value().get<std::string>()));
		}
		else if (key == "FontSize")
		{
			SetFontSize(element.value().get<float>());
		}
		else if (key == "FontColor")
		{
			SetFontColor(JsonSerializer::Json2Color(element.value()));
		}
		else if (key == "TextAlignment")
		{
			SetTextAlignment(JsonSerializer::Json2Enum<DWRITE_TEXT_ALIGNMENT>(element.value()));
		}
		else if (key == "ParagraphAlignment")
		{
			SetParagraphAlignment(JsonSerializer::Json2Enum<DWRITE_PARAGRAPH_ALIGNMENT>(element.value()));
		}
		else if (key == "OrderInLayer")
		{
			SetOrderInLayer(element.value().get<int>());
		}
		else if (key == "Canvas")
		{
			GameObject* pObj = pIGameObjectFinder->Find(element.value().get<std::string>());
			SetCanvas(*pObj->GetComponent<Renderings::Canvas>());
		}
		else
		{
			Utility::Throw();
		}
	}
}
