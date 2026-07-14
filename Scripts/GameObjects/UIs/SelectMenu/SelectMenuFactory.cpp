/*
 * FileName:     SelectMenuFactory.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * 選択メニュー工場
 */

#include "Pch.h"
#include "SelectMenuFactory.h"

#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/Renderings/Image.h"
#include "Scripts/Commons/Components/RectTransform.h"
#include "SelectMenu.h"

// 選択メニューを作成
std::unique_ptr<GameObject> SelectMenuFactory::Create
(
	IComponentManager*        pIComponentManager,
	float                     width,
	const Math::Color&        color,
	const Math::Vector2&      position,
	Utility::AlignmentPoint   anchor,
	const Renderings::Canvas& canvas,
	SelectMenu**              ppSelectMenu
)
{
	std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>(pIComponentManager);
	auto* pSelectMenu = gameObject->AddComponent<SelectMenu>();
	pSelectMenu->Initialize(pIComponentManager, width, color, position, anchor, canvas);
	if (ppSelectMenu)
	{
		*ppSelectMenu = pSelectMenu;
	}
	return gameObject;
}
