/*
 * FileName:     GameObject.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
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
	, m_pComponents{}
	, m_pIComponentManager{ pIComponentManager }
{
}