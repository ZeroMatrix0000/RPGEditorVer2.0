/*
 * FileName:     Action.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/07
 *
 * アクション
 */

#include "Pch.h"
#include "Action.h"

#include "Scripts/Commons/Systems/IErrorMessage.h"

 // コンストラクタ
Action::Action()
	: m_isNext{}
{
}

// 開始処理
void Action::Enter(GamePlaySceneInternals* pInternals)
{
}

// 更新処理
void Action::Update(GamePlaySceneInternals* pInternals, float elapsedTime)
{
	// 次のアクションに移動
	GoNext();
	// エラーメッセージの追加
	Systems::IErrorMessage::GetInstance()->AddMessage(L"不明なアクションです。");
}

// 終了処理
void Action::Exit(GamePlaySceneInternals* pInternals)
{
}
