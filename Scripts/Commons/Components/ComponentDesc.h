/*
 * FileName:     ComponentDesc.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/17
 *
 * コンポーネント概要
 */

#pragma once

namespace GameObjects
{
	class GameObject;
	class IGameObjectInstantiator;
}

namespace Components
{
	class ComponentCreatePermit;

	// コンポーネント概要
	struct ComponentDesc
	{

		/* メンバ関数 */

		// コンストラクタ
		ComponentDesc(GameObject* pOwner, IGameObjectInstantiator* pIGameObjectInstantiator, const ComponentCreatePermit&)
			: pOwner{ pOwner }
			, pIGameObjectInstantiator{ pIGameObjectInstantiator }
		{
		}


		/* メンバ変数 */

		// 所有者のポインタ
		GameObject* pOwner;
		// ゲームオブジェクト生成インタフェース
		IGameObjectInstantiator* pIGameObjectInstantiator;

	};
}
