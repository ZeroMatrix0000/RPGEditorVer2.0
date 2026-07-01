/*
 * FileName:     Scene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * シーン
 */

#pragma once

#include "../GameObjects/Component.h"

namespace Scenes
{
	template<typename TTransitionData, typename TContext>
	class Scene : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Scene(const ComponentCreatePermit& permit)
			: Component{ permit }
			, m_pContext{}
		{
		}

		// 初期化処理
		virtual void Initialize(const TTransitionData& data) {};
		// 終了処理
		virtual void Finalize() {};

		// コンテキストを設定
		void SetContext(const TContext& context) { m_pContext = &context; }


	protected:


		/* メンバ関数 */

		// コンテキストを取得
		const TContext& GetContext() const { return *m_pContext; }


	private:


		/* メンバ変数 */

		// コンテキストのポインタ
		const TContext* m_pContext;

	};
}
