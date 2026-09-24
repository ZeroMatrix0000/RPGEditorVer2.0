/*
 * FileName:     PixelShader.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/23
 *
 * ピクセルシェーダ
 */

#include "Pch.h"
#include "PixelShader.h"

// コンストラクタ
Renderings::PixelShader::PixelShader()
	: m_d3dShader{}
	, m_constantBuffer{}
{
}

// 初期化処理
void Renderings::PixelShader::Initialize(ID3D11Device5* device, const std::wstring& filePath)
{
	// ブロブデータ
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	Utility::ThrowIfFailed(D3DReadFileToBlob(filePath.c_str(), blob.GetAddressOf()));

	// ピクセルシェーダ
	Utility::ThrowIfFailed(device->CreatePixelShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		m_d3dShader.GetAddressOf()
	));

	m_constantBuffer = std::make_unique<ConstantBuffer>();
	m_constantBuffer->Initialize(blob.Get());
}

// 生成
Renderings::PixelShader Renderings::PixelShader::Create(ID3D11Device5* device, const std::wstring& filePath)
{
	PixelShader shader;
	shader.Initialize(device, filePath);
	return shader;
}
