/*
 * FileName:     Text.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
 *
 * テキスト
 */

#include "Pch.h"
#include "Text.h"

#include "ITextRenderer.h"

// コンストラクタ
Renderings::Text::Text(const ComponentCreatePermit& permit, GameObject* pOwner, ITextRenderer* pITextRenderer)
	: Component{ permit, pOwner }
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
