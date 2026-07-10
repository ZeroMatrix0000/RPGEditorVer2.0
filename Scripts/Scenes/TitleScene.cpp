/*
 * FileName:     TitleScene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * タイトルシーン
 */

#include "Pch.h"
#include "TitleScene.h"

#include "Scripts/Commons/Renderings/Canvas.h"
#include "../Main/GameContext.h"
#include "../UIs/SelectMenu/SelectMenuFactory.h"
#include "../UIs/SelectMenu/SelectMenu.h"

// コンストラクタ
TitleScene::TitleScene(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Scene{ permit, pOwner }
	, m_canvas{}
	, m_selectMenu{}
	, m_pSelectMenu{}
{
}

// 初期化処理
void TitleScene::Initialize(const SceneTransitionData& data)
{
	// コンテキスト
	const auto& gameContext = GetContext();

	// 出力サイズ
	const Math::Vector2& outputSize = gameContext.GetIWindowController().GetOutputSize();

	// コンポーネント工場
	const auto& iComponentManager = gameContext.GetIComponentManager();

	// キャンバスを作成
	auto* pCanvas = m_canvas.AddComponent<Renderings::Canvas>(iComponentManager);
	pCanvas->Initialize(Renderings::Canvas::FixedSize::Vertical, outputSize);

	// 選択メニューを作成
	SelectMenuFactory::Create
	(
		iComponentManager,
		350.0f,
		Math::Color{ 1.0f, 0.95f, 0.8f, 1.0f },
		Math::Vector2{ 0.0f, 200.0f },
		Utility::AlignmentPoint::MiddleCenter,
		Utility::AlignmentPoint::MiddleCenter,
		*pCanvas,
		&m_selectMenu,
		nullptr,
		&m_pSelectMenu
	);
	m_pSelectMenu->AddOption(iComponentManager, L"スタート", [&] { gameContext.GetISceneManager().SetNextScene<TitleScene>(); });
	m_pSelectMenu->AddOption(iComponentManager, L"エディタ", [&] { gameContext.GetISceneManager().SetNextScene<TitleScene>(); });
	m_pSelectMenu->AddOption(iComponentManager, L"ゲームを終了", [&] { gameContext.GetIWindowController().Destroy(); });
}

// 更新処理
void TitleScene::Update(float elapsedTime)
{
	// シーン切り替え中でないなら
	if (!GetContext().GetISceneManager().IsChanging())
	{
		// 入力管理
		const auto& iInput = GetContext().GetIInput();

		// W or ↑ で上選択
		if (iInput.GetKeyDown(KeyName::W) || iInput.GetKeyDown(KeyName::Up))
		{
			m_pSelectMenu->SelectUp();
		}
		// S or ↓ で下選択
		if (iInput.GetKeyDown(KeyName::S) || iInput.GetKeyDown(KeyName::Down))
		{
			m_pSelectMenu->SelectDown();
		}
		// Z or Space で実行
		if (iInput.GetKeyDown(KeyName::Z) || iInput.GetKeyDown(KeyName::Space))
		{
			m_pSelectMenu->Execute();
		}
	}

	// 選択メニューの更新
	m_selectMenu.Update(elapsedTime);
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
		const Math::Vector2& outputSize = GetContext().GetIWindowController().GetOutputSize();
		// キャンバスのサイズを設定
		m_canvas.GetComponent<Renderings::Canvas>()->SetSize(outputSize);
	}
}
