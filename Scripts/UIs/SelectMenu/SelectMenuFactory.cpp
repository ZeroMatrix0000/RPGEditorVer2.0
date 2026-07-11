/*
 * FileName:     SelectMenuFactory.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/10
 *
 * 選択メニュー工場
 */

#include "Pch.h"
#include "SelectMenuFactory.h"

#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/GameObjects/RectTransform.h"
#include "SelectMenu.h"

// 選択メニューを作成
void SelectMenuFactory::Create
(
	const IComponentManager&  iComponentManager,
	float                     width,
	const Math::Color&        color,
	const Math::Vector2&      position,
	Utility::AlignmentPoint   pivot,
	Utility::AlignmentPoint   anchor,
	const Renderings::Canvas& canvas,
	GameObject*               pGameObject,
	SelectMenu**              ppSelectMenu
)
{
	auto* pSelectMenu = pGameObject->AddComponent<SelectMenu>(iComponentManager);
	pSelectMenu->Initialize(iComponentManager, width, color, position, anchor, canvas);
	if (ppSelectMenu)
	{
		*ppSelectMenu = pSelectMenu;
	}
}
