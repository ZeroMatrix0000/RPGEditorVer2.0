/*
 * FileName:     TitleScene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
 *
 * タイトルシーン
 */

#include "Pch.h"
#include "TitleScene.h"

#include "Scripts/Commons/Systems/IWindowController.h"
#include "Scripts/Commons/Systems/IInput.h"
#include "Scripts/Commons/Scenes/ISceneManager.h"
#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/GameObjects/IGameObjectManager.h"
#include "Scripts/Main/GameContext.h"
#include "Scripts/GameObjects/UIs/SelectMenu/SelectMenu.h"

// コンストラクタ
TitleScene::TitleScene(const ComponentDesc& desc)
	: Scene{ desc }
	, m_pCanvas{}
	, m_pSelectMenu{}
{
}

// 初期化処理
void TitleScene::Initialize(const SceneTransitionData& data)
{
	// コンテキスト
	const auto& gameContext = GetContext();

	// 出力サイズ
	const Math::Vector2& outputSize = gameContext.GetPIWindowController()->GetOutputSize();

	// ゲームオブジェクト管理
	auto* pIGameObjectManager = gameContext.GetPIGameObjectManager();

	pIGameObjectManager->SetPGameObjects(GetPGameObjects());
	pIGameObjectManager->Load("Scene_Title");

	// キャンバスを取得
	m_pCanvas = pIGameObjectManager->Find("Canvas")->GetComponent<Renderings::Canvas>();
	m_pCanvas->SetSize(outputSize);

	// 選択メニューを取得
	m_pSelectMenu = pIGameObjectManager->Find("TitleMenu")->GetComponent<SelectMenu>();
	m_pSelectMenu->AddOption(L"スタート", [&] { gameContext.GetPISceneManager()->SetNextScene<TitleScene>(); });
	m_pSelectMenu->AddOption(L"エディタ", [&] { gameContext.GetPISceneManager()->SetNextScene<TitleScene>(); });
	m_pSelectMenu->AddOption(L"ゲームを終了", [&] { gameContext.GetPIWindowController()->Destroy(); });
}

// 更新処理
void TitleScene::Update(float elapsedTime)
{
	// シーン切り替え中でないなら
	if (!GetContext().GetPISceneManager()->IsChanging())
	{
		// 入力管理
		auto* pIInput = GetContext().GetPIInput();

		// W or ↑ で上選択
		if (pIInput->GetKeyDown(KeyName::W) || pIInput->GetKeyDown(KeyName::Up))
		{
			m_pSelectMenu->SelectUp();
		}
		// S or ↓ で下選択
		if (pIInput->GetKeyDown(KeyName::S) || pIInput->GetKeyDown(KeyName::Down))
		{
			m_pSelectMenu->SelectDown();
		}
		// Z or Space で実行
		if (pIInput->GetKeyDown(KeyName::Z) || pIInput->GetKeyDown(KeyName::Space))
		{
			m_pSelectMenu->Execute();
		}
	}

	// 選択メニューの更新
	m_pSelectMenu->Update(elapsedTime);
}

// 終了処理
void TitleScene::Finalize()
{
}

// メッセージを受け取る
void TitleScene::AcceptMessage(const std::string& message)
{
	if (message == "WindowSizeChanged")
	{
		// 出力サイズ
		const Math::Vector2& outputSize = GetContext().GetPIWindowController()->GetOutputSize();
		// キャンバスのサイズを設定
		m_pCanvas->SetSize(outputSize);
	}
}
