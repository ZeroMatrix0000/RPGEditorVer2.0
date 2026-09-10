/*
 * FileName:     ActionOpenMessageWindow.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/10
 *
 * メッセージウィンドウ開アクション
 */

#include "Pch.h"
#include "ActionOpenMessageWindow.h"

#include "Scripts/GameObjects/UIs/MessageWindow/MessageWindow.h"
#include "Scripts/Commons/Systems/JsonSerializer.h"

// コンストラクタ
ActionOpenMessageWindow::ActionOpenMessageWindow(const ComponentDesc& desc)
	: Action{ desc }
	, m_isWait{}
	, m_pMessageWindow{ GetPOwner()->GetNullReferences<MessageWindow>() }
{
}

// 初期化処理
void ActionOpenMessageWindow::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_pMessageWindow, "MessageWindow");
	serializer.Load(json);
}

// パラメータを設定
void ActionOpenMessageWindow::SetParams(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_isWait, "IsWait");
	serializer.Load(json);
}

// 開始処理
void ActionOpenMessageWindow::Enter()
{
	// ダイアログボックスを出現
	m_pMessageWindow->Appear(true);
	// テキストを初期化
	m_pMessageWindow->SetText();
	m_pMessageWindow->SetCharacter();
}

// 更新処理
void ActionOpenMessageWindow::Update(float elapsedTime, const IGameInput& iGameInput)
{
	// 開き終わるまで待たないか、開き終わったなら次のアクションへ移動
	if (!m_isWait || !m_pMessageWindow->IsMoving())
	{
		GoNext();
	}
}
