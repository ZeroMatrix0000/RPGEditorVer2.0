/*
 * FileName:     Model3D.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
 *
 * 3Dモデル
 */

#include "Pch.h"
#include "Model3D.h"

#include "IModel3DRenderer.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/IGameObjectFinder.h"
#include "../Renderings/CameraScreen.h"

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
	// 要素ごとにループ
	for (const auto& element : json.items())
	{
		const std::string& key = element.key();
		if (key == "ModelSourceName")
		{
			SetModelSourceName(element.value().get<std::string>());
		}
		else if (key == "CameraScreen")
		{
			for (const auto& cameraScreen : element.value())
			{
				GameObject* pObj = pIGameObjectFinder->Find(cameraScreen.get<std::string>());
				AddICameraScreen(*pObj->GetComponent<Renderings::ICameraScreen>());
			}
		}
		else
		{
			Utility::Throw();
		}
	}
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
