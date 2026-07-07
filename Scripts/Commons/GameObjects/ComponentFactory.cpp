/*
 * FileName:     ComponentFactory.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/07
 *
 * コンポーネント工場
 */

#include "Pch.h"
#include "ComponentFactory.h"

// コンストラクタ
GameObjects::ComponentFactory::ComponentFactory()
	: OnlyOne{ typeid(ComponentFactory) }
	, m_permit{}
	, m_pIModelRenderer{}
	, m_pIImageRenderer{}
	, m_pITextRenderer{}
{
}

// 初期化処理
void GameObjects::ComponentFactory::Initialize
(
	Renderings::IModel3DRenderer* pIModelRenderer,
	Renderings::IImageRenderer*   pIImageRenderer,
	Renderings::ITextRenderer*    pITextRenderer
)
{
	m_pIModelRenderer = pIModelRenderer;
	m_pIImageRenderer = pIImageRenderer;
	m_pITextRenderer  = pITextRenderer;
}
