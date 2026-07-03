/*
 * FileName:     GameObject.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * ゲームオブジェクト
 */

#include "Pch.h"
#include "GameObject.h"

#include "Component.h"

// コンストラクタ
GameObjects::GameObject::GameObject()
	: m_components{}
{
}

// 更新処理
void GameObjects::GameObject::Update(float elapsedTime)
{
	for (auto& component : m_components)
	{
		component.second->Update(elapsedTime);
	}
}
