/*
 * FileName:     Image.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
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
	, m_orderInLayer{}
	, m_pCanvas{}
	, m_pIImageRenderer{ pIImageRenderer }
{
	m_pIImageRenderer->AddPImage(this);
}

// デストラクタ
Renderings::Image::~Image()
{
	m_pIImageRenderer->RemovePImage(this);
}
