/*
 * FileName:     SceneManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * シーン管理
 */

#pragma once

#include "ISceneManager.h"
#include "Scene.h"

namespace Scenes
{
	template<typename TTransitionData, typename TContext>
	class SceneManager : public ISceneManager<TTransitionData>
	{

		typedef Scene<TTransitionData, TContext> Scene;


	public:


		/* メンバ関数 */

		// コンストラクタ
		SceneManager(const TContext& context)
			: ISceneManager<TTransitionData>{}
			, m_currentScene{}
			, m_nextScene{}
			, m_CreateComponentList{}
			, m_refContext{ context }
		{
		}

		// 更新処理
		void Update(float elapsedTime)
		{
			// シーンの更新
			m_currentScene->Update(Math::Min(elapsedTime, 1.0f / 30.0f));
		}
		// 終了処理
		void Finalize()
		{
			// シーンの終了
			m_currentScene->Finalize();
		}

		// ウィンドウサイズ変更時の処理
		void OnWindowSizeChanged()
		{
			m_currentScene->AcceptMessage("WindowSizeChanged");
		}

		// シーンを追加
		void AddScene(const std::string& sceneName, const std::function<std::unique_ptr<Scene>()>& CreateComponent)
		{
			m_CreateComponentList.emplace(sceneName, CreateComponent);
		}

		// はじめのシーンを設定
		void SetFirstScene(const std::string& sceneName, const TTransitionData& data = TTransitionData{})
		{
			// シーンの初期化
			m_currentScene = m_CreateComponentList.at(sceneName)();
			m_currentScene->SetContext(m_refContext);
			m_currentScene->Initialize(data);
		}

		// 次のシーンを設定
		void SetNextScene(const std::string& sceneName, const TTransitionData& data = TTransitionData{}) override
		{
			m_nextScene = m_CreateComponentList.at(sceneName)();
		}

		// シーン切り替え中かどうか
		bool IsChanging() const override { return false; }


	private:


		/* メンバ変数 */

		// 現在のシーン
		std::unique_ptr<Scene> m_currentScene;
		// 次のシーン
		std::unique_ptr<Scene> m_nextScene;

		// コンポーネント作成関数
		std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>> m_CreateComponentList;

		// コンテキスト
		const TContext& m_refContext;

	};
}
