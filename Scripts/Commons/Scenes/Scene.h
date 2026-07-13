/*
 * FileName:     Scene.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * シーン
 */

#pragma once

#include "../GameObjects/Component.h"

namespace GameObjects
{
	class GameObject;
}

namespace Scenes
{
	// シーン
	template<typename TTransitionData, typename TContext>
	class Scene : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Scene(const ComponentCreatePermit& permit, GameObject* pOwner)
			: Component{ permit, pOwner }
			, m_gameObjects{}
			, m_pContext{}
		{
		}

		// 初期化処理
		virtual void Initialize(const TTransitionData& data) = 0;
		// 終了処理
		virtual void Finalize() = 0;

		// コンテキストを設定
		void SetContext(const TContext& context) { m_pContext = &context; }


	protected:


		/* メンバ関数 */

		// ゲームオブジェクトリストを取得
		std::unordered_map<std::string, std::unique_ptr<GameObject>>* GetPGameObjects() { return &m_gameObjects; }

		// コンテキストを取得
		const TContext& GetContext() const { return *m_pContext; }


	private:


		/* メンバ変数 */

		// ゲームオブジェクトリスト
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;

		// コンテキストのポインタ
		const TContext* m_pContext;

	};
}
