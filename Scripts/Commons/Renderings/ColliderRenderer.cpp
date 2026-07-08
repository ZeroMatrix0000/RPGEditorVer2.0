/*
 * FileName:     ColliderRenderer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * 図形描画
 */

#include "Pch.h"
#include "ColliderRenderer.h"

#include "../Colliders/BoxCollider.h"
#include "../Renderings/ICameraScreen.h"

 // コンストラクタ
Renderings::ColliderRenderer::ColliderRenderer()
	: IColliderRenderer{}
	, m_primitiveBatch{}
	, m_basicEffect{}
	, m_pBoxColliders{}
	, m_pContext{}
	, m_pCommonStates{}
	, m_inputLayout{}
{
}

// 初期化処理
void Renderings::ColliderRenderer::Initialize(ID3D11Device5* pDevice, ID3D11DeviceContext4* pContext, const DirectX::CommonStates& commonStates)
{
	m_pContext      = pContext;
	m_pCommonStates = &commonStates;

	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(pContext);
	m_basicEffect    = std::make_unique<DirectX::BasicEffect>(pDevice);
	m_basicEffect->SetVertexColorEnabled(true);
	Utility::ThrowIfFailed
	(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(pDevice, m_basicEffect.get(), m_inputLayout.ReleaseAndGetAddressOf())
	);
}

// 描画処理
void Renderings::ColliderRenderer::Render()
{
	m_pContext->OMSetBlendState(m_pCommonStates->Opaque(), nullptr, 0xFFFFFFFF);
	m_pContext->OMSetDepthStencilState(m_pCommonStates->DepthDefault(), 0);
	m_pContext->RSSetState(m_pCommonStates->CullNone());

	m_basicEffect->Apply(m_pContext);
	m_pContext->IASetInputLayout(m_inputLayout.Get());

	// 描画開始
	m_primitiveBatch->Begin();

	// 長方形
	for (const auto* pBoxCollider : m_pBoxColliders)
	{
		// カメラ画面
		for (const auto* pICameraScreen : pBoxCollider->GetPICameraScreens())
		{
			m_basicEffect->SetMatrices(Math::Matrix::Identity, pICameraScreen->GetViewMatrix(), pICameraScreen->GetProjectionMatrix());
			DrawBox(pBoxCollider->GetWorldBox(), pBoxCollider->GetColor());
		}
	}

	// 描画終了
	m_primitiveBatch->End();
}

// 長方形当たり判定のポインタを追加
void Renderings::ColliderRenderer::AddPBoxCollider(const Colliders::BoxCollider* pBoxCollider)
{
	m_pBoxColliders.emplace(pBoxCollider);
}

// 長方形当たり判定のポインタを削除
void Renderings::ColliderRenderer::RemovePBoxCollider(const Colliders::BoxCollider* pBoxCollider)
{
	m_pBoxColliders.erase(pBoxCollider);
}

// 直方体を描画
void Renderings::ColliderRenderer::DrawBox(const Math::Box& box, const Math::Color& color) const
{
	// 頂点情報
	DirectX::VertexPositionColor vertexes[] =
	{
		DirectX::VertexPositionColor{ Math::Vector3{ -0.5f, -0.5f, -0.5f }, color },
		DirectX::VertexPositionColor{ Math::Vector3{ -0.5f, -0.5f,  0.5f }, color },
		DirectX::VertexPositionColor{ Math::Vector3{ -0.5f,  0.5f, -0.5f }, color },
		DirectX::VertexPositionColor{ Math::Vector3{ -0.5f,  0.5f,  0.5f }, color },
		DirectX::VertexPositionColor{ Math::Vector3{  0.5f, -0.5f, -0.5f }, color },
		DirectX::VertexPositionColor{ Math::Vector3{  0.5f, -0.5f,  0.5f }, color },
		DirectX::VertexPositionColor{ Math::Vector3{  0.5f,  0.5f, -0.5f }, color },
		DirectX::VertexPositionColor{ Math::Vector3{  0.5f,  0.5f,  0.5f }, color }
	};

	uint16_t indexes[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7,
		0, 2, 1, 3, 4, 6, 5, 7,
		0, 4, 1, 5, 2, 6, 3, 7
	};

	// 変換行列
	Math::Matrix matrix =
		Math::Matrix::CreateScale(box.size) *
		Math::Matrix::CreateFromQuaternion(box.rotation) *
		Math::Matrix::CreateTranslation(box.position)
	;
	// 座標を変換
	for(auto& vertex : vertexes)
	{
		vertex.position = Math::Vector3::Transform(vertex.position, matrix);
	}

	m_primitiveBatch->DrawIndexed(D3D11_PRIMITIVE_TOPOLOGY_LINELIST, indexes, 24, vertexes, 8);
}
