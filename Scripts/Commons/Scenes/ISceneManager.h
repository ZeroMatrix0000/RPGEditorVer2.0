/*
 * FileName:     ISceneManager.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 * 
 * シーン管理のインタフェース
 */

#pragma once

#include "../Systems/OnlyOne.h"

namespace Scenes
{
	// シーン管理のインタフェース
	template<typename TTransitionData>
	class ISceneManager : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ISceneManager()
			: OnlyOne{ typeid(ISceneManager) }
		{
		}
		// デストラクタ
		virtual ~ISceneManager() = default;

		// 次のシーンを設定
		virtual void SetNextScene(const std::string& sceneName, const TTransitionData& data = TTransitionData{}) = 0;

		// シーン切り替え中かどうか
		virtual bool IsChanging() const = 0;

	};
}
