/*
 * FileName:     Component.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/17
 *
 * コンポーネント
 */

#include "Pch.h"
#include "Component.h"

#include "ComponentDesc.h"
#include "../GameObjects/IGameObjectInstantiator.h"

// コンストラクタ
Components::Component::Component(const ComponentDesc& desc)
	: m_pOwner{ desc.pOwner }
	, m_pIGameObjectInstantiator{ desc.pIGameObjectInstantiator }
{
}

// ゲームオブジェクトを生成
GameObject* Components::Component::Instantiate(const std::string& name) const
{
	return m_pIGameObjectInstantiator->Instantiate(name);
}
