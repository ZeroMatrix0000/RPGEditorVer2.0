/*
 * FileName:     GameObject.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * ゲームオブジェクト
 */

#include "Pch.h"
#include "GameObject.h"

#include "Component.h"

// コンストラクタ
Objects::GameObject::GameObject()
	: m_components{}
{
}
