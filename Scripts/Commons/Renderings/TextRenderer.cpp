/*
 * FileName:     TextRenderer.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * テキスト描画
 */

#include "Pch.h"
#include "TextRenderer.h"

#include "Text.h"
#include "Canvas.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/RectTransform.h"
#include "../Systems/IErrorMessage.h"

// コンストラクタ
Renderings::TextRenderer::TextRenderer()
	: ITextRenderer{}
	, m_d2DFactory{}
	, m_dWriteFactory{}
	, m_renderTarget{}
	, m_fontCollection{}
	, m_pTexts{}
{
}

// 初期化処理
void Renderings::TextRenderer::Initialize(IDXGISwapChain4* pSwapChain)
{
	// Direct2Dファクトリー
	if (m_d2DFactory.Get() == nullptr)
	{
		Utility::ThrowIfFailed(D2D1CreateFactory
		(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			m_d2DFactory.ReleaseAndGetAddressOf()
		));
	}

	// DirectWrite
	if (m_dWriteFactory.Get() == nullptr)
	{
		Utility::ThrowIfFailed(DWriteCreateFactory
		(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory8),
			reinterpret_cast<IUnknown**>(m_dWriteFactory.ReleaseAndGetAddressOf())
		));
	}

	// バックバッファ
	Microsoft::WRL::ComPtr<IDXGISurface2> pBackBuffer;
	Utility::ThrowIfFailed(pSwapChain->GetBuffer(0, IID_PPV_ARGS(pBackBuffer.GetAddressOf())));

	// プロパティ
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties
	(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	// レンダーターゲット
	Utility::ThrowIfFailed(m_d2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer.Get(), &props, m_renderTarget.GetAddressOf()));
}

// フォントコレクションの作成
void Renderings::TextRenderer::CreateFontCollection(const std::wstring& directoryPath)
{
	// パスが存在しないなら
	if (!std::filesystem::exists(directoryPath))
	{
		// エラーメッセージを追加
		Systems::IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
		(
			L"パスが間違っています。: %s",
			directoryPath.c_str()
		));
		return;
	}

	// フォントファイル
	std::vector<Microsoft::WRL::ComPtr<IDWriteFontFile>> fontFiles;

	// ディレクトリ内を全て検索
	for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath))
	{
		// ファイルなら
		if (entry.is_regular_file())
		{
			fontFiles.push_back(Microsoft::WRL::ComPtr<IDWriteFontFile>{});
			if (FAILED(m_dWriteFactory->CreateFontFileReference(entry.path().c_str(), nullptr, &fontFiles.back())))
			{
				fontFiles.pop_back();
				// エラーメッセージを追加
				Systems::IErrorMessage::GetInstance()->AddMessage(Utility::FormatWString
				(
					L"フォントの読み込みに失敗しました。: %s",
					entry.path().c_str()
				));
			}
		}
	}

	// ビルダー
	Microsoft::WRL::ComPtr<IDWriteFontSetBuilder2> builder;
	Utility::ThrowIfFailed(m_dWriteFactory->CreateFontSetBuilder(builder.GetAddressOf()));

	for (const auto& fontFile : fontFiles)
	{
		Utility::ThrowIfFailed(builder->AddFontFile(fontFile.Get()));
	}

	// フォントセット
	Microsoft::WRL::ComPtr<IDWriteFontSet> fontSet;
	Utility::ThrowIfFailed(builder->CreateFontSet(fontSet.GetAddressOf()));

	// フォントコレクション
	Microsoft::WRL::ComPtr<IDWriteFontCollection1> fontCollection;
	Utility::ThrowIfFailed(m_dWriteFactory->CreateFontCollectionFromFontSet
	(
		fontSet.Get(),
		fontCollection.GetAddressOf()
	));
	Utility::ThrowIfFailed(fontCollection.As(&m_fontCollection));
}

// 描画開始
void Renderings::TextRenderer::Begin()
{
	// 描画開始
	m_renderTarget->BeginDraw();
}

// 描画処理
void Renderings::TextRenderer::Draw(const Text* pText)
{
	// モデルの所有者の2Dトランスフォーム
	const RectTransform* pRectTransform = pText->GetPOwner()->GetConstComponent<RectTransform>();
	if (!pRectTransform)
	{
		return;
	}

	// モデルが映るキャンバス
	const Canvas* pCanvas = pText->GetPCanvas();
	if (!pCanvas)
	{
		return;
	}

	// 長方形
	Math::Rect rect = pRectTransform->GetRect();
	// キャンバスサイズ
	Math::Vector2 canvasSize = pCanvas->GetSize();

	// ピボットに合わせて長方形を移動
	switch (pRectTransform->GetPivot())
	{
	case Utility::AlignmentPoint::TopLeft:
		rect.position.x += rect.size.x / 2.0f;
		rect.position.y += rect.size.y / 2.0f;
		break;
	case Utility::AlignmentPoint::TopCenter:
		rect.position.y += rect.size.y / 2.0f;
		break;
	case Utility::AlignmentPoint::TopRight:
		rect.position.x -= rect.size.x / 2.0f;
		rect.position.y += rect.size.y / 2.0f;
		break;
	case Utility::AlignmentPoint::MiddleLeft:
		rect.position.x += rect.size.x / 2.0f;
		break;
	case Utility::AlignmentPoint::MiddleCenter:
		break;
	case Utility::AlignmentPoint::MiddleRight:
		rect.position.x -= rect.size.x / 2.0f;
		break;
	case Utility::AlignmentPoint::BottomLeft:
		rect.position.x += rect.size.x / 2.0f;
		rect.position.y -= rect.size.y / 2.0f;
		break;
	case Utility::AlignmentPoint::BottomCenter:
		rect.position.y -= rect.size.y / 2.0f;
		break;
	case Utility::AlignmentPoint::BottomRight:
		rect.position.x -= rect.size.x / 2.0f;
		rect.position.y -= rect.size.y / 2.0f;
		break;
	default:
		break;
	}
	// アンカーに合わせて長方形を移動
	switch (pRectTransform->GetAnchor())
	{
	case Utility::AlignmentPoint::TopCenter:
		rect.position.x += canvasSize.x / 2.0f;
		break;
	case Utility::AlignmentPoint::TopRight:
		rect.position.x += canvasSize.x;
		break;
	case Utility::AlignmentPoint::MiddleLeft:
		rect.position.y += canvasSize.y / 2.0f;
		break;
	case Utility::AlignmentPoint::MiddleCenter:
		rect.position.x += canvasSize.x / 2.0f;
		rect.position.y += canvasSize.y / 2.0f;
		break;
	case Utility::AlignmentPoint::MiddleRight:
		rect.position.x += canvasSize.x;
		rect.position.y += canvasSize.y / 2.0f;
		break;
	case Utility::AlignmentPoint::BottomLeft:
		rect.position.y += canvasSize.y;
		break;
	case Utility::AlignmentPoint::BottomCenter:
		rect.position.x += canvasSize.x / 2.0f;
		rect.position.y += canvasSize.y;
		break;
	case Utility::AlignmentPoint::BottomRight:
		rect.position.x += canvasSize.x;
		rect.position.y += canvasSize.y;
		break;
	default:
		break;
	}

	// キャンバスの表示倍率
	float canvasRatio = pCanvas->GetRatio();
	// 表示倍率を適用
	rect.position *= canvasRatio;
	rect.size *= canvasRatio;

	// ブラシ
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBrush;
	m_renderTarget->CreateSolidColorBrush
	(
		pText->GetFontColor(),
		pBrush.GetAddressOf()
	);

	// テキストフォーマット
	Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat;
	if (FAILED(m_dWriteFactory->CreateTextFormat
	(
		pText->GetFontName().c_str(),
		m_fontCollection.Get(),
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		pText->GetFontSize() * canvasRatio,
		L"ja-jp",
		pTextFormat.GetAddressOf()
	)))
	{
		return;
	}

	// 左右配置
	pTextFormat->SetTextAlignment(pText->GetTextAlignment());
	// 上下配置
	pTextFormat->SetParagraphAlignment(pText->GetParagraphAlignment());

	// 角度
	float angle = pRectTransform->GetAngle();
	// 描画ターゲットを回転
	if (angle != 0.0f)
	{
		m_renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation
		(
			angle,
			D2D1::Point2F(rect.position.x, rect.position.y)
		));
	}

	// 描画する文字列
	const std::wstring& str = pText->GetStr();
	// 文字列を描画
	m_renderTarget->DrawTextW
	(
		str.c_str(),
		static_cast<int>(str.size()),
		pTextFormat.Get(),
		rect.CreateD2D1_RECT_F(),
		pBrush.Get()
	);

	// 描画ターゲットの角度を戻す
	if (angle != 0.0f)
	{
		m_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	m_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

// 描画終了
void Renderings::TextRenderer::End()
{
	// 描画終了
	m_renderTarget->EndDraw();
}

// リセット
void Renderings::TextRenderer::Reset()
{
	m_renderTarget.Reset();
}

// テキストのポインタを追加
void Renderings::TextRenderer::AddPText(const Text* pText)
{
	m_pTexts.push_back(pText);
}

// テキストのポインタを削除
void Renderings::TextRenderer::RemovePText(const Text* pText)
{
	auto it = std::ranges::find(m_pTexts, pText);
	if (it != m_pTexts.end())
	{
		m_pTexts.erase(it);
	}
}

// テキストのポインタリストをソート
void Renderings::TextRenderer::SortPTexts()
{
	// レイヤー順にソート
	std::ranges::sort(m_pTexts, [](const Text* p1, const Text* p2) {return p1->GetOrderInLayer() < p2->GetOrderInLayer(); });
}
