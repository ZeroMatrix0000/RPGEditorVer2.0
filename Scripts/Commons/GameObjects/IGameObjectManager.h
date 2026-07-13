/*
 * FileName:     IGameObjectManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * ゲームオブジェクト管理のインタフェース
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace GameObjects
{
	class IComponentManager;
	class GameObject;

	// ゲームオブジェクト管理のインタフェース
	class IGameObjectManager : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		IGameObjectManager()
			: OnlyOne{ typeid(IGameObjectManager) }
		{
		}

		// ゲームオブジェクトを読み込む
		virtual void Load
		(
			const IComponentManager& iComponentManager,
			const std::string& jsonName,
			std::unordered_map<std::string, std::unique_ptr<GameObject>>* pGameObjects
		) const = 0;

	};
}
