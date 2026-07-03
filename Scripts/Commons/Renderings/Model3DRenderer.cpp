/*
 * FileName:     Model3DRenderer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/02
 *
 * 3Dモデル描画
 */

#include "Pch.h"
#include "Model3DRenderer.h"

#include "Model3D.h"
#include "ICameraScreen.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Transform.h"
#include "../Systems/IResources.h"

 // コンストラクタ
Renderings::Model3DRenderer::Model3DRenderer(const Systems::IResources& iResources)
	: IModel3DRenderer{}
	, m_pModels{}
	, m_pContext{}
	, m_pCommonStates{}
	, m_refIResources{ iResources }
{
}

// 初期化処理
void Renderings::Model3DRenderer::Initialize(ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates)
{
	m_pContext = pContext;
	m_pCommonStates = &commonStates;
}

// 描画処理
void Renderings::Model3DRenderer::Render()
{
	for (const auto* pModel : m_pModels)
	{
		// モデルソース
		const Model3DSource* modelSource = m_refIResources.GetModelSource(pModel->GetModelSourceName());
		if (!modelSource)
		{
			return;
		}

		// カメラ画面のインタフェース
		const ICameraScreen* pICameraScreen = pModel->GetPICameraScreen();
		if (!pICameraScreen)
		{
			return;
		}

		// モデルの所有者のトランスフォーム
		const Transform* pTransform = pModel->GetPOwner()->GetConstComponent<Transform>();
		if (!pTransform)
		{
			return;
		}

		modelSource->GetModel().Draw
		(
			m_pContext,
			*m_pCommonStates,
			Math::Matrix::CreateTranslation(pTransform->GetPosition()),
			pICameraScreen->GetViewMatrix(),
			pICameraScreen->GetProjectionMatrix()
		);
	}
}

// モデルのポインタを追加
void Renderings::Model3DRenderer::AddModel(const Model3D* pModel)
{
	m_pModels.emplace(pModel);
}

// モデルのポインタを削除
void Renderings::Model3DRenderer::RemoveModel(const Model3D* pModel)
{
	m_pModels.erase(pModel);
}
