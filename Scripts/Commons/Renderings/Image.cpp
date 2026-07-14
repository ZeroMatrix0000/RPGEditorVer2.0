/*
 * FileName:     Image.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * 画像
 */

#include "Pch.h"
#include "Image.h"

#include "IImageRenderer.h"

// コンストラクタ
Renderings::Image::Image(const ComponentCreatePermit& permit, GameObject* pOwner, IImageRenderer* pIImageRenderer)
	: Component{ permit, pOwner }
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
void Renderings::Image::Initalize(const nlohmann::ordered_json& json)
{
	// 要素ごとにループ
	for (const auto& element : json.items())
	{
		const std::string& key = element.key();
		if (key == "ImageSourceName")
		{
			SetImageSourceName(element.value().get<std::string>());
		}
		else if (key == "Color")
		{
			SetColor(JsonSerializer::Json2Color(element.value()));
		}
		else if (key == "OrderInLayer")
		{
			SetOrderInLayer(element.value().get<int>());
		}
		else
		{
			Utility::Throw();
		}
	}
}

// 画像サイズを取得
Math::Vector2 Renderings::Image::GetSize() const
{
	return m_pIImageRenderer->GetImageSize(this);
}
