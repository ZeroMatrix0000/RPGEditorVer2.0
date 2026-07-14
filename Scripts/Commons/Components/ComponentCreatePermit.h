/*
 * FileName:     ComponentCreateInfo.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * コンポーネント作成許可証
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace Components
{
	// コンポーネント作成許可証
	class ComponentCreatePermit : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ComponentCreatePermit()
			: OnlyOne{ typeid(ComponentCreatePermit) }
		{
		}

	};
}
