/*
 * FileName:     Component.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * コンポーネント
 */

#pragma once

#include "Observer.h"

// 前方宣言
namespace Systems
{
	class ComponentCreatePermit;
}

namespace Objects
{
	// 前方宣言
	class GameObject;

	class Component : public Observer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Component(Systems::ComponentCreatePermit&)
			: m_pOwner{}
		{
		}
		// デストラクタ
		virtual ~Component() = default;

		// 更新処理
		virtual void Update() = 0;


	private:


		/* メンバ変数 */

		// 所有者のポインタ
		GameObject* m_pOwner;

	};
}
