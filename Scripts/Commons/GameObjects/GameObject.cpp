/*
 * FileName:     GameObject.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
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
