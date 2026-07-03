/*
 * FileName:     ComponentFactory.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * コンポーネント工場
 */

#include "Pch.h"
#include "ComponentFactory.h"

// コンストラクタ
GameObjects::ComponentFactory::ComponentFactory()
	: OnlyOne{ typeid(ComponentFactory) }
	, m_permit{}
	, m_pIModelRenderer{}
{
}
