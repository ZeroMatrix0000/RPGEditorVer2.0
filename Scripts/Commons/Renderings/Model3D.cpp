/*
 * FileName:     Model3D.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * 3Dモデル
 */

#include "Pch.h"
#include "Model3D.h"

#include "IModel3DRenderer.h"

Renderings::Model3D::Model3D(const ComponentCreatePermit& permit, GameObject* pOwner, IModel3DRenderer* pIModelRenderer)
	: Component{ permit, pOwner }
	, m_modelSourceName{}
	, m_pICameraScreens{}
	, m_pIModelRenderer{ pIModelRenderer }
{
	// 描画者にモデルを追加
	m_pIModelRenderer->AddPModel(this);
}

// デストラクタ
Renderings::Model3D::~Model3D()
{
	// 描画者からモデルを削除
	m_pIModelRenderer->RemovePModel(this);
}

// 映るカメラ画面を追加
void Renderings::Model3D::AddICameraScreen(const ICameraScreen& iCameraScreen)
{
	m_pICameraScreens.emplace(&iCameraScreen);
}

// 映るカメラ画面を削除
void Renderings::Model3D::RemoveICameraScreen(const ICameraScreen& iCameraScreen)
{
	m_pICameraScreens.erase(&iCameraScreen);
}
