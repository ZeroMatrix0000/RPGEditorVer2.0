/*
 * FileName:     Image.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
 *
 * 画像
 */

#include "Pch.h"
#include "Image.h"

#include "IImageRenderer.h"
#include "../GameObjects/IGameObjectFinder.h"
#include "../GameObjects/GameObject.h"
#include "../Renderings/Canvas.h"
#include "../Systems/JsonSerializer.h"

// コンストラクタ
Renderings::Image::Image(const ComponentDesc& desc, IImageRenderer* pIImageRenderer)
	: Component{ desc }
	, m_imageSourceName{}
	, m_color{ DirectX::Colors::White }
	, m_orderInLayer{}
	, m_pCanvas{}
	, m_pIImageRenderer{ pIImageRenderer }
{
	// 画像描画にポインタを追加
	m_pIImageRenderer->AddPImage(this);
}

// デストラクタ
Renderings::Image::~Image()
{
	// 画像描画からポインタを削除
	m_pIImageRenderer->RemovePImage(this);
}

// 初期化処理
void Renderings::Image::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_imageSourceName, "ImageSourceName");
	serializer.AddParameter(&m_color, "Color");
	serializer.AddParameter(&m_pixelShaderName, "PixelShaderName");
	serializer.AddParameter(&m_orderInLayer, "OrderInLayer");
	serializer.AddParameter(&m_pCanvas, "Canvas");
	serializer.Load(json);
}

// 画像サイズを取得
Math::Vector2 Renderings::Image::GetSize() const
{
	return m_pIImageRenderer->GetImageSize(this);
}
