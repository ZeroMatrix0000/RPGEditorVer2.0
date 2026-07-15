/*
 * FileName:     ComponentDesc.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/15
 *
 * コンポーネント概要
 */

#pragma once

namespace GameObjects
{
	class GameObject;
	class IIGameObjectManager;
}

namespace Components
{
	class ComponentCreatePermit;

	// コンポーネント概要
	struct ComponentDesc
	{

		/* メンバ変数 */

		// 所有者のポインタ
		GameObject* pOwner;
		// コンポーネント作成許可証の参照
		const ComponentCreatePermit& refPermit;


	};
}
