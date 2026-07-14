/*
 * FileName:     ErrorMessage.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * エラーメッセージ
 */

#include "Pch.h"
#include "ErrorMessage.h"

#include "../GameObjects/GameObject.h"
#include "../GameObjects/RectTransform.h"
#include "../Renderings/Text.h"
#include "../Renderings/Canvas.h"

// コンストラクタ
Systems::ErrorMessage::ErrorMessage()
	: IErrorMessage{}
	, m_messages{}
	, m_messageCount{}
	, m_text{}
	, m_textComponent{}
	, m_canvas{}
	, m_fontName{}
	, m_displayTime{}
	, m_isActive{}
{
}

// 初期化処理
void Systems::ErrorMessage::Initialize(const std::wstring& fontName, float displayTime, bool isActive)
{
	m_messageCount = 0;

	m_fontName = fontName;

	m_displayTime = displayTime;

	m_isActive = isActive;
}

// 更新処理
void Systems::ErrorMessage::Update(float elapsedTime)
{
	// メッセージ数が変わったら表示を適用
	if (m_messageCount != m_messages.size())
	{
		m_messageCount = m_messages.size();
		ApplyDisplayText();
	}

	// メッセージのどれかを消したか
	bool isErased = false;

	for (int i = 0; i < m_messages.size(); i++)
	{
		m_messages.at(i).timer += elapsedTime;
		// 表示時間を超えたらメッセージを消す
		if (m_messages.at(i).timer.IsMax())
		{
			auto it = m_messages.begin() + i;
			isErased = true;
			m_messages.erase(it);
			i--;
		}
	}

	// メッセージがどれか消えていたら表示を適用
	if (isErased)
	{
		ApplyDisplayText();
	}
}

// オブジェクト生成
void Systems::ErrorMessage::CreateObjects(IComponentManager* pIComponentManager)
{
	// テキストの設定
	m_text = std::make_unique<GameObject>(pIComponentManager);
	auto* pRectTransform = m_text->AddComponent<RectTransform>();
	pRectTransform->SetPosition(Math::Vector2{ 10.0f, 10.0f });
	pRectTransform->SetSize(Math::Vector2{ 100000.0f, 100000.0f });
	pRectTransform->SetPivot(Utility::AlignmentPoint::TopLeft);
	pRectTransform->SetAnchor(Utility::AlignmentPoint::TopLeft);
	m_textComponent = m_text->AddComponent<Renderings::Text>();
	m_textComponent->SetStr(L"");
	m_textComponent->SetFontName(m_fontName);
	m_textComponent->SetFontSize(24.0f);
	m_textComponent->SetFontColor(DirectX::Colors::Yellow);
	m_textComponent->SetOrderInLayer(65535);
	// キャンバスの設定
	m_canvas = std::make_unique<GameObject>(pIComponentManager);
	auto* pCanvas = m_canvas->AddComponent<Renderings::Canvas>();
	pCanvas->Initialize(Renderings::Canvas::FixedSize::None, Math::Vector2{ 1600.0f, 900.0f });

	// キャンバスに画像を映す
	m_textComponent->SetCanvas(*pCanvas);
}

// メッセージを追加
void Systems::ErrorMessage::AddMessage(const std::wstring& text)
{
	// アクティブでないなら何もしない
	if (!m_isActive)
	{
		return;
	}

	m_messages.push_back(MessageData{ text, Limited::Create(0.0f, 0.0f, m_displayTime) });
}

// 表示を適用
void Systems::ErrorMessage::ApplyDisplayText()
{
	std::wstring str = L"";

	// 各メッセージのテキストを追加
	for (const auto& message : m_messages)
	{
		str += message.text + L"\n";
	}

	m_textComponent->SetStr(str);
}
