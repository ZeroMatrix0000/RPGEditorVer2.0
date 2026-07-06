/*
 * FileName:     Model3D.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 3Dモデル
 */

#pragma once

#include "../GameObjects/Component.h"

namespace Renderings
{
	// 3Dモデル
	class Model3D : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Model3D(const ComponentCreatePermit& permit, GameObject* pOwner);

		// モデルソース名を設定
		void SetModelSourceName(const std::string& modelSourceName) { m_modelSourceName = modelSourceName; }

		// モデルソース名を取得
		const std::string& GetModelSourceName() const { return m_modelSourceName; }


	private:


		/* メンバ変数 */

		// モデルソース名
		std::string m_modelSourceName;

	};
}
