/*
 * FileName:     SelectMenu.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
 *
 * 選択メニュー
 */

#include "Pch.h"
#include "SelectMenu.h"

#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Components/RectTransform.h"
#include "Scripts/Commons/GameObjects/IGameObjectFinder.h"

// コンストラクタ
SelectMenu::SelectMenu(const ComponentDesc& desc)
	: Component{ desc }
	, m_params{}
	, m_selectNumber{}
	, m_cursorDelayY{}
	, m_cursorSwayTimer{}
	, m_Processes{}
	, m_pCursorImage{}
	, m_pCursorRectTransform{}
{
}

// 初期化処理
void SelectMenu::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	if (m_pCursorImage == nullptr)
	{
		GameObject* pObj = Instantiate("Prefab_SelectMenuCursor");
		m_pCursorImage = pObj->GetComponent<Renderings::Image>();
		m_pCursorRectTransform = pObj->GetComponent<RectTransform>();
	}

	// 選択番号を初期化
	m_selectNumber = 0;
	// カーソルのY座標のズレ
	m_cursorDelayY.SetMovement(0.0f, 0.0f);

	// 要素ごとにループ
	for (const auto& element : json.items())
	{
		const std::string& key = element.key();
		if (key == "Width")
		{
			m_params.width = element.value().get<float>();
		}
		else if (key == "Height")
		{
			m_params.height = element.value().get<float>();
		}
		else if (key == "Interval")
		{
			m_params.interval = element.value().get<float>();
		}
		else if (key == "Position")
		{
			m_params.basePosition = JsonSerializer::Json2Vector2(element.value());
		}
		else if (key == "CursorMoveTime")
		{
			m_params.cursorMoveTime = element.value().get<float>();
		}
		else if (key == "CursorEasingType")
		{
			m_params.cursorEasingType = JsonSerializer::Json2Enum<Easing::Type>(element.value());
		}
		else if (key == "CursorEasingInOut")
		{
			m_params.cursorEasingInOut = JsonSerializer::Json2Enum<Easing::InOut>(element.value());
		}
		else if (key == "CursorSwayTime")
		{
			m_cursorSwayTimer.Initialize(0.0f, 0.0f, element.value().get<float>());
		}
		else if (key == "CursorSwaySize")
		{
			m_params.cursorSwaySize = element.value().get<float>();
		}
		else if (key == "Canvas")
		{
			GameObject* pObj = pIGameObjectFinder->Find(element.value().get<std::string>());
			m_pCursorImage->SetCanvas(*pObj->GetComponent<Renderings::Canvas>());
		}
		else
		{
			Utility::Throw();
		}
	}
}

// 更新処理
void SelectMenu::Update(float elapsedTime)
{
	// 表示座標
	Math::Vector2 position = m_params.basePosition;

	// カーソルのY座標のズレを更新
	m_cursorDelayY.Tick(elapsedTime);
	// カーソルの左右のズレの周期を更新
	m_cursorSwayTimer += elapsedTime;

	// カーソルの左右のズレ
	Math::Vector2 cursorDelay = Math::Vector2
	{
		m_params.cursorSwaySize * Math::Sin(m_cursorSwayTimer.GetRatio() * 2.0f * Math::PI),
		(m_params.height + m_params.interval) * m_cursorDelayY.GetMovement()
	};

	// カーソルの位置を変更
	m_pCursorRectTransform->SetPosition(m_params.basePosition + Math::Vector2{ -m_params.width / 2.0f, 0.0f } + cursorDelay);
}

// 選択肢を追加
void SelectMenu::AddOption(const std::wstring& str, const std::function<void()>& Process)
{
	GameObject* gameObject = Instantiate("Prefab_SelectMenuText");
	auto* pText = gameObject->AddComponent<Renderings::Text>();
	pText->SetStr(str);
	pText->SetCanvas(*m_pCursorImage->GetPCanvas());
	auto* pRectTransform = gameObject->AddComponent<RectTransform>();
	pRectTransform->SetPosition(m_params.basePosition + Math::Vector2{ 0.0f, m_params.height + m_params.interval } * static_cast<float>(m_Processes.size()));
	pRectTransform->SetSize(Math::Vector2{ m_params.width, m_params.height });
	m_Processes.push_back(Process);
}

// 上の項目を選択
void SelectMenu::SelectUp()
{
	if (m_Processes.size() == 0)
	{
		return;
	}
	m_selectNumber = (m_selectNumber + m_Processes.size() - 1) % static_cast<int>(m_Processes.size());
	m_cursorDelayY.SetMovement(static_cast<float>(m_selectNumber), m_params.cursorMoveTime, m_params.cursorEasingType, m_params.cursorEasingInOut);
}

// 下の項目を選択
void SelectMenu::SelectDown()
{
	if (m_Processes.size() == 0)
	{
		return;
	}
	m_selectNumber = (m_selectNumber + 1) % static_cast<int>(m_Processes.size());
	m_cursorDelayY.SetMovement(static_cast<float>(m_selectNumber), m_params.cursorMoveTime, m_params.cursorEasingType, m_params.cursorEasingInOut);
}

// 実行
void SelectMenu::Execute()
{
	if (m_Processes.size() == 0)
	{
		return;
	}
	m_Processes.at(m_selectNumber)();
}
