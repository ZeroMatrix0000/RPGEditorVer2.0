/*
 * FileName:     ComponentCreateInfo.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * コンポーネント作成許可証
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace GameObjects
{
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
