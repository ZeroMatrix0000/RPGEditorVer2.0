/*
 * FileName:     ComponentFactory.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * コンポーネント工場
 */

#pragma once

#include "OnlyOne.h"
#include "ComponentCreatePermit.h"

// 前方宣言
namespace Objects
{
	class Component;
}

namespace Systems
{
	class ComponentFactory : public OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ComponentFactory()
			: OnlyOne{ typeid(ComponentFactory) }
			, m_permit{}
		{
		}

		// コンポーネントを作成
		template<typename T> requires IsDerived<T, Component>
		std::unique_ptr<T> Create() {};


		/* メンバ変数 */

		// コンポーネント作成許可証
		ComponentCreatePermit m_permit;

	};
}
