/*
 * FileName:     MessageWindow.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/09/07
 *
 * メッセージウィンドウ
 */

#include "Pch.h"
#include "MessageWindow.h"

#include "Scripts/Commons/Renderings/Canvas.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Renderings/Text.h"
#include "Scripts/Commons/Systems/JsonSerializer.h"

// コンストラクタ
MessageWindow::MessageWindow(const ComponentDesc& desc)
	: Component{ desc }
{
}

// 初期化処理
void MessageWindow::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	const Renderings::Canvas* pCanvas = nullptr;

	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&pCanvas, "Canvas");
	serializer.Load(json);

	// キャンバスを生成
	GameObject* pObj = Instantiate("Prefab_MessageWindowBackGround");
	pObj->GetComponent<Renderings::Image>()->SetCanvas(*pCanvas);
	pObj = Instantiate("Prefab_MessageWindowCharacter");
	pObj->GetComponent<Renderings::Text>()->SetCanvas(*pCanvas);
	pObj = Instantiate("Prefab_MessageWindowText");
	pObj->GetComponent<Renderings::Text>()->SetCanvas(*pCanvas);

}
