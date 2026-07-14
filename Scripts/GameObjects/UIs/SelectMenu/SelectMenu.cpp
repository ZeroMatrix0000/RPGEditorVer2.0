/*
 * FileName:     SelectMenu.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * 選択メニュー
 */

#include "Pch.h"
#include "SelectMenu.h"

#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Components/RectTransform.h"

// コンストラクタ
SelectMenu::SelectMenu(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Component{ permit, pOwner }
	, m_width{}
	, m_basePosition{}
	, m_cursor{}
	, m_pCursorRectTransform{}
	, m_texts{}
	, m_Processes{}
	, m_selectNumber{}
	, m_cursorDelayY{}
	, m_cursorSwayTimer{}
{
}

// 初期化処理
void SelectMenu::Initalize(const nlohmann::ordered_json& json)
{
}

// 初期化処理
void SelectMenu::Initialize
(
	IComponentManager*        pIComponentManager,
	float                     width,
	const Math::Color&        color,
	const Math::Vector2&      position,
	Utility::AlignmentPoint   anchor,
	const Renderings::Canvas& canvas
)
{
	m_width = width;
	m_basePosition = position;

	// 選択番号を初期化
	m_selectNumber = 0;
	// カーソルのY座標のズレ
	m_cursorDelayY.SetMovement(0.0f, 0.0f);
	// カーソルの左右の揺れ
	m_cursorSwayTimer.Initialize(0.0f, 0.0f, CURSOR_SWAY_TIME);

	m_cursor = std::make_unique<GameObject>(pIComponentManager);
	auto* pImage = m_cursor->AddComponent<Renderings::Image>();
	pImage->SetImageSourceName("MenuRight");
	pImage->SetColor(color);
	pImage->SetCanvas(canvas);
	m_pCursorRectTransform = m_cursor->AddComponent<RectTransform>();
	m_pCursorRectTransform->SetPosition(position);
	m_pCursorRectTransform->SetAnchor(anchor);
	m_pCursorRectTransform->SetSize(pImage->GetSize() / 2.0f);
}

// 更新処理
void SelectMenu::Update(float elapsedTime)
{
	// 表示座標
	Math::Vector2 position = m_basePosition;

	// カーソルのY座標のズレを更新
	m_cursorDelayY.Tick(elapsedTime);
	// カーソルの左右のズレの周期を更新
	m_cursorSwayTimer += elapsedTime;

	// カーソルの左右のズレ
	Math::Vector2 cursorDelay = Math::Vector2
	{
		CURSOR_SWAY_SIZE * Math::Sin(m_cursorSwayTimer.GetRatio() * 2.0f * Math::PI),
		(HEIGHT + INTERVAL) * m_cursorDelayY.GetMovement()
	};

	// カーソルの位置を変更
	m_pCursorRectTransform->SetPosition(m_basePosition + Math::Vector2{ -m_width / 2.0f, 0.0f } + cursorDelay);
}

// 選択肢を追加
void SelectMenu::AddOption(IComponentManager* pIComponentManager, const std::wstring& str, const std::function<void()>& Process)
{
	std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>(pIComponentManager);
	auto* pText = gameObject->AddComponent<Renderings::Text>();
	pText->SetStr(str);
	pText->SetFontName(L"GenEi M Gothic v2");
	pText->SetFontSize(40.0f);
	pText->SetFontColor(m_cursor->GetComponent<Renderings::Image>()->GetColor());
	pText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pText->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	pText->SetCanvas(*m_cursor->GetComponent<Renderings::Image>()->GetPCanvas());
	auto* pRectTransform = gameObject->AddComponent<RectTransform>();
	pRectTransform->SetPosition(m_basePosition + Math::Vector2{ 0.0f, HEIGHT + INTERVAL } * static_cast<float>(m_texts.size()));
	pRectTransform->SetAnchor(m_pCursorRectTransform->GetAnchor());
	pRectTransform->SetSize(Math::Vector2{ m_width, HEIGHT });
	m_texts.push_back(std::move(gameObject));
	m_Processes.push_back(Process);
}

// 上の項目を選択
void SelectMenu::SelectUp()
{
	if (m_texts.size() == 0)
	{
		return;
	}
	m_selectNumber = (m_selectNumber + m_texts.size() - 1) % static_cast<int>(m_texts.size());
	m_cursorDelayY.SetMovement(static_cast<float>(m_selectNumber), CURSOR_MOVE_TIME, Easing::Type::Expo, Easing::InOut::Out);
}

// 下の項目を選択
void SelectMenu::SelectDown()
{
	if (m_texts.size() == 0)
	{
		return;
	}
	m_selectNumber = (m_selectNumber + 1) % static_cast<int>(m_texts.size());
	m_cursorDelayY.SetMovement(static_cast<float>(m_selectNumber), CURSOR_MOVE_TIME, Easing::Type::Expo, Easing::InOut::Out);
}

// 実行
void SelectMenu::Execute()
{
	if (m_texts.size() == 0)
	{
		return;
	}
	m_Processes.at(m_selectNumber)();
}
