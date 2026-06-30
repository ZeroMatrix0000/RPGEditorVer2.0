/*
 * FileName:     Scene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * シーン
 */

#pragma once

#include "Component.h"

namespace Objects
{
	template<typename T>
	class Scene : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Scene(Systems::ComponentCreatePermit& permit)
			: Component{ permit }
		{
		}

	};
}
