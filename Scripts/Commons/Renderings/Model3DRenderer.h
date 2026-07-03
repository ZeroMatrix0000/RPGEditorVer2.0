/*
 * FileName:     Model3DRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/02
 *
 * 3Dモデル描画
 */

#pragma once

#include "IModel3DRenderer.h"

 // 前方宣言
namespace Systems
{
	class IResources;
}

namespace Renderings
{
	class Model3DRenderer : public IModel3DRenderer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		Model3DRenderer(const Systems::IResources& iResources);

		// 初期化処理
		void Initialize(ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates);
		// 描画処理
		void Render();

		// モデルのポインタを追加
		void AddModel(const Model3D* pModel) override;
		// モデルのポインタを削除
		void RemoveModel(const Model3D* pModel) override;


	private:


		/* メンバ変数 */

		// モデルのポインタリスト
		std::unordered_set<const Model3D*> m_pModels;

		// コンテキストのポインタ
		ID3D11DeviceContext4* m_pContext;
		// コモンステートのポインタ
		const DirectX::CommonStates* m_pCommonStates;

		// リソースのインタフェースの参照
		const Systems::IResources& m_refIResources;

	};
}
