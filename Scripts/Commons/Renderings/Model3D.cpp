/*
 * FileName:     Model3D.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/03
 *
 * 3Dモデル
 */

#include "Pch.h"
#include "Model3D.h"

#include "IModel3DRenderer.h"

Renderings::Model3D::Model3D(const ComponentCreatePermit& permit, GameObject* pOwner, IModel3DRenderer* pIModelRenderer)
	: Component{ permit, pOwner }
	, m_modelSourceName{}
	, m_pIModelRenderer{ pIModelRenderer }
	, m_pICameraScreen{}
{
	// 描画者にモデルを追加
	m_pIModelRenderer->AddModel(this);
}

// デストラクタ
Renderings::Model3D::~Model3D()
{
	// 描画者からモデルを削除
	m_pIModelRenderer->RemoveModel(this);
}
