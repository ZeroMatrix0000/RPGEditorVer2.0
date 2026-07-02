/*
 * FileName:     SampleScene.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/02
 *
 * サンプルシーン
 */

#include "Pch.h"
#include "SampleScene.h"

#include "Scripts/Commons/GameObjects/Transform.h"
#include "Scripts/Commons/Renderings/Model3D.h"

// コンストラクタ
SampleScene::SampleScene(const ComponentCreatePermit& permit)
	: Scene{ permit }
	, m_test{}
{
}

// 初期化処理
void SampleScene::Initialize(const SceneTransitionData& data)
{
	// コンポーネント工場
	const auto& componentFactory = GetContext().GetComponentFactory();

	// コンポーネントをアタッチ
	m_test.AddComponent<Transform>(componentFactory);
	auto* pModel3D = m_test.AddComponent<Renderings::Model3D>(componentFactory);
	pModel3D->SetModelName("Player");
}
