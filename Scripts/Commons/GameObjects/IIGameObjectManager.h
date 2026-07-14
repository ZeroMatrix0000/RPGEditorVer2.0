/*
 * FileName:     IIGameObjectManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * ゲームオブジェクト管理インタフェースのインタフェース
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace GameObjects
{
	class GameObject;

	// ゲームオブジェクト管理インタフェースのインタフェース
	class IIGameObjectManager : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		IIGameObjectManager()
			: OnlyOne{ typeid(IIGameObjectManager) }
		{
		}

		// ゲームオブジェクトを名前で検索
		virtual GameObject* Find(const std::string& name) const = 0;

		// ゲームオブジェクトを生成
		virtual GameObject* Instantiate(const std::string& jsonName) const = 0;

	};
}
