/*
 * FileName:     SelectMenuFactory.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * 選択メニュー工場
 */

#pragma once

namespace Renderings
{
	class Canvas;
	class Image;
}
namespace GameObjects
{
	class GameObject;
	class RectTransform;
	class IComponentManager;
}
class SelectMenu;

// 選択メニュー工場
namespace SelectMenuFactory
{
	// 選択メニューを作成
	void Create
	(
		const IComponentManager&  iComponentManager,
		float                     width,
		const Math::Color&        color,
		const Math::Vector2&      position,
		Utility::AlignmentPoint   anchor,
		const Renderings::Canvas& canvas,
		GameObject*               pGameObject,
		SelectMenu**              ppSelectMenu
	);
}
