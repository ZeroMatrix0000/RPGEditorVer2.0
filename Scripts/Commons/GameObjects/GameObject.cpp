/*
 * FileName:     GameObject.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * ゲームオブジェクト
 */

#include "Pch.h"
#include "GameObject.h"

#include "../Components/Component.h"

// コンストラクタ
GameObjects::GameObject::GameObject(IComponentManager* pIComponentManager)
	: m_name{}
	, m_components{}
	, m_pIComponentManager{ pIComponentManager }
{
}

// 更新処理
void GameObjects::GameObject::Update(float elapsedTime)
{
	// コンポーネントを更新
	for (auto& component : m_components)
	{
		component.second->Update(elapsedTime);
	}
}
