/*
 * FileName:     MessageWindow.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/08
 *
 * メッセージウィンドウ
 */

#include "Pch.h"
#include "MessageWindow.h"

#include "Scripts/Commons/Components/RectTransform.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/Systems/JsonSerializer.h"

// コンストラクタ
MessageWindow::MessageWindow(const ComponentDesc& desc)
	: Component{ desc }
	, m_moveTime{}
	, m_backgroundSize{}
	, m_characterSize{}
	, m_textSize{}
	, m_characterFontSize{}
	, m_textFontSize{}
	, m_moveRate{}
	, m_pBackgroundTransform{ GetPOwner()->GetNullReferences<RectTransform>() }
	, m_pBackground{ GetPOwner()->GetNullReferences<Renderings::Image>() }
	, m_pTextTransform{ GetPOwner()->GetNullReferences<RectTransform>() }
	, m_pText{ GetPOwner()->GetNullReferences<Renderings::Text>() }
	, m_pCharacterTransform{ GetPOwner()->GetNullReferences<RectTransform>() }
	, m_pCharacter{ GetPOwner()->GetNullReferences<Renderings::Text>() }
{
}

// 初期化処理
void MessageWindow::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{

	const Renderings::Canvas* pCanvas = nullptr;

	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_moveTime, "MoveTime");
	serializer.AddParameter(&pCanvas, "Canvas");
	serializer.Load(json);

	// メッセージウィンドウを生成
	GameObject* pObj = Instantiate("Prefab_MessageWindowBackGround");
	m_pBackgroundTransform = pObj->GetComponent<RectTransform>();
	m_pBackground = pObj->GetComponent<Renderings::Image>();
	m_pBackground->SetCanvas(*pCanvas);
	pObj = Instantiate("Prefab_MessageWindowCharacter");
	m_pCharacterTransform = pObj->GetComponent<RectTransform>();
	m_pCharacter = pObj->GetComponent<Renderings::Text>();
	m_pCharacter->SetCanvas(*pCanvas);
	pObj = Instantiate("Prefab_MessageWindowText");
	m_pTextTransform = pObj->GetComponent<RectTransform>();
	m_pText = pObj->GetComponent<Renderings::Text>();
	m_pText->SetCanvas(*pCanvas);

	// 移動率を初期化
	m_moveRate.SetMovement(0.0f, 0.0f);

	// サイズを取得
	m_backgroundSize = m_pBackgroundTransform->GetRect().size;
	m_characterSize = m_pCharacterTransform->GetRect().size;
	m_textSize = m_pTextTransform->GetRect().size;
	m_characterFontSize = m_pCharacter->GetFontSize();
	m_textFontSize = m_pText->GetFontSize();

	// 非表示
	m_pBackgroundTransform->SetSize(Math::Vector2::Zero);
	m_pCharacterTransform->SetSize(Math::Vector2::Zero);
	m_pTextTransform->SetSize(Math::Vector2::Zero);
	m_pCharacter->SetFontSize(0.0f);
	m_pText->SetFontSize(0.0f);

}

// 更新処理
void MessageWindow::Update(float elapsedTime)
{
	// 移動率を更新
	m_moveRate.Tick(elapsedTime);
	// 移動率
	float moveRate = m_moveRate.GetMovement();

	if (moveRate == 0.0f)
	{
		return;
	}

	// 透明度を変更
	Math::Color color = m_pBackground->GetColor();
	color.w = moveRate;
	m_pBackground->SetColor(color);
	color = m_pCharacter->GetFontColor();
	color.w = moveRate;
	m_pCharacter->SetFontColor(color);
	color = m_pText->GetFontColor();
	color.w = moveRate;
	m_pText->SetFontColor(color);

	// サイズを変更
	m_pBackgroundTransform->SetSize(Math::Vector2::Lerp(Math::Vector2::Zero, m_backgroundSize, moveRate));
	m_pCharacterTransform->SetSize(Math::Vector2::Lerp(Math::Vector2::Zero, m_characterSize, moveRate));
	m_pTextTransform->SetSize(Math::Vector2::Lerp(Math::Vector2::Zero, m_textSize, moveRate));

	// フォントサイズを変更
	m_pCharacter->SetFontSize(m_characterFontSize * moveRate);
	m_pText->SetFontSize(m_textFontSize * moveRate);
}

// 出現
void MessageWindow::Appear(bool isAppear)
{
	m_moveRate.SetMovement
	(
		isAppear ? 0.0f : 1.0f,
		isAppear ? 1.0f : 0.0f,
		m_moveTime,
		Easing::Type::Back,
		isAppear ? Easing::InOut::Out : Easing::InOut::In
	);
}
