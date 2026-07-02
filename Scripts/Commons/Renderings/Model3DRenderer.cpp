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
