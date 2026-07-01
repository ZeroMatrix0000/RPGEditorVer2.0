/*
 * FileName:     Model3D.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * 3Dモデル
 */

#pragma once

#include "../GameObjects/Component.h"

namespace Renderings
{
	class Model3D : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Model3D(const ComponentCreatePermit& permit, GameObject* pOwner);

		// モデル名を設定
		void SetModelName(const std::string& modelName) { m_modelName = modelName; }


	private:


		/* メンバ変数 */

		// モデル名
		std::string m_modelName;

	};
}
