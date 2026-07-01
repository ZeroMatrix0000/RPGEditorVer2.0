/*
 * FileName:     Model3DRenderer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * 3Dモデル描画
 */

#include "Pch.h"
#include "Model3DRenderer.h"

#include "../Systems/IResources.h"

 // コンストラクタ
Renderings::Model3DRenderer::Model3DRenderer(const Systems::IResources& resources)
	: OnlyOne{ typeid(Model3DRenderer) }
	, m_resources{ resources }
	, m_pContext{}
	, m_pCommonStates{}
{
}

// 初期化処理
void Renderings::Model3DRenderer::Initialize(ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates)
{
	m_pContext = pContext;
	m_pCommonStates = &commonStates;
}
