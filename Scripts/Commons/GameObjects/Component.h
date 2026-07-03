/*
 * FileName:     Component.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * コンポーネント
 */

#pragma once

#include "Observer.h"

namespace GameObjects
{
	// 前方宣言
	class GameObject;
	class ComponentCreatePermit;

	class Component : public Observer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Component(const ComponentCreatePermit&, GameObject* pOwner)
			: m_pOwner{ pOwner }
		{
		}
		// デストラクタ
		virtual ~Component() = default;

		// 更新処理
		virtual void Update(float elapsedTime) {};

		// 所有者を取得
		const GameObject* GetPOwner() const { return m_pOwner; }


	private:


		/* メンバ変数 */

		// 所有者のポインタ
		GameObject* m_pOwner;

	};
}
