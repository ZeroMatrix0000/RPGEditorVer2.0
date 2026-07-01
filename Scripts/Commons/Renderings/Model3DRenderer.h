/*
 * FileName:     Model3DRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * 3Dモデル描画
 */

#pragma once

#include "../Systems/OnlyOne.h"

 // 前方宣言
namespace Systems
{
	class IResources;
}

namespace Renderings
{
	class Model3DRenderer : public Systems::OnlyOne
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Model3DRenderer(const Systems::IResources& resources);

		// 初期化処理
		void Initialize(ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates);


	private:


		/* メンバ変数 */

		// リソース
		const Systems::IResources& m_resources;

		// コンテキスト
		ID3D11DeviceContext4* m_pContext;
		// コモンステート
		const DirectX::CommonStates* m_pCommonStates;

	};
}
