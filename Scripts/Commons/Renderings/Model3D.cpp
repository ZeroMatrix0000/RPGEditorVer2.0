/*
 * FileName:     Model3D.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/22
 *
 * 3Dモデル
 */

#include "Pch.h"
#include "Model3D.h"

#include "IModel3DRenderer.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/IGameObjectFinder.h"
#include "../Renderings/CameraScreen.h"
#include "../Systems/JsonSerializer.h"

Renderings::Model3D::Model3D(const ComponentDesc& desc, IModel3DRenderer* pIModelRenderer)
	: Component{ desc }
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

// 初期化処理
void Renderings::Model3D::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_modelSourceName, "ModelSourceName");
	serializer.AddParameter(&m_pICameraScreens, "CameraScreens");
	serializer.Load(json);
}

// 映るカメラ画面を追加
void Renderings::Model3D::AddICameraScreen(const ICameraScreen& iCameraScreen)
{
	if (std::ranges::find(m_pICameraScreens, &iCameraScreen) == m_pICameraScreens.end())
	{
		m_pICameraScreens.push_back(&iCameraScreen);
	}
}

// 映るカメラ画面を削除
void Renderings::Model3D::RemoveICameraScreen(const ICameraScreen& iCameraScreen)
{
	auto it = std::ranges::find(m_pICameraScreens, &iCameraScreen);
	if (it != m_pICameraScreens.end())
	{
		m_pICameraScreens.erase(it);
	}
}
